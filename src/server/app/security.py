from fastapi import HTTPException, Security, Depends
from fastapi.security import APIKeyHeader, OAuth2PasswordBearer
import jwt
import secrets
import logging
import hashlib
import ssl
from datetime import datetime, timedelta
from typing import Optional, Dict, List
from ipaddress import ip_network, ip_address

logger = logging.getLogger(__name__)

class SecurityManager:
    def __init__(self):
        self.secret_key = secrets.token_urlsafe(32)
        self.api_key_header = APIKeyHeader(name="X-API-Key")
        self.allowed_devices = {}  # device_id: api_key mapping
        self.blocked_ips = set()
        self.failed_attempts = {}
        self.allowed_networks = [ip_network("192.168.0.0/16")]  # Local network only
        
    def generate_api_key(self, device_id: str) -> str:
        """Generate a new API key for a device."""
        api_key = secrets.token_urlsafe(32)
        self.allowed_devices[device_id] = {
            'api_key': api_key,
            'created_at': datetime.utcnow(),
            'last_used': None
        }
        return api_key
    
    def verify_api_key(self, api_key: str) -> bool:
        """Verify if API key is valid."""
        for device_info in self.allowed_devices.values():
            if device_info['api_key'] == api_key:
                device_info['last_used'] = datetime.utcnow()
                return True
        return False
    
    def generate_token(self, device_id: str, expires_delta: Optional[timedelta] = None) -> str:
        """Generate JWT token for device."""
        if expires_delta:
            expire = datetime.utcnow() + expires_delta
        else:
            expire = datetime.utcnow() + timedelta(days=30)
            
        to_encode = {
            "device_id": device_id,
            "exp": expire,
            "iat": datetime.utcnow()
        }
        return jwt.encode(to_encode, self.secret_key, algorithm="HS256")
    
    def decode_token(self, token: str) -> Dict:
        """Decode and verify JWT token."""
        try:
            payload = jwt.decode(token, self.secret_key, algorithms=["HS256"])
            return payload
        except jwt.ExpiredSignatureError:
            raise HTTPException(
                status_code=401,
                detail="Token has expired"
            )
        except jwt.JWTError:
            raise HTTPException(
                status_code=401,
                detail="Could not validate token"
            )
    
    def is_ip_allowed(self, client_ip: str) -> bool:
        """Check if IP is allowed to access the server."""
        if client_ip in self.blocked_ips:
            return False
            
        ip = ip_address(client_ip)
        return any(ip in network for network in self.allowed_networks)
    
    def handle_failed_attempt(self, ip: str):
        """Handle failed authentication attempts."""
        if ip not in self.failed_attempts:
            self.failed_attempts[ip] = {
                'count': 1,
                'first_attempt': datetime.utcnow()
            }
        else:
            self.failed_attempts[ip]['count'] += 1
            
        # Block IP if too many failed attempts
        if self.failed_attempts[ip]['count'] >= 5:
            self.blocked_ips.add(ip)
            logger.warning(f"IP {ip} blocked due to too many failed attempts")
    
    def setup_ssl_context(self) -> ssl.SSLContext:
        """Set up SSL context with secure configuration."""
        context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
        context.minimum_version = ssl.TLSVersion.TLSv1_3
        context.set_ciphers('ECDHE+AESGCM:ECDHE+CHACHA20')
        context.load_cert_chain('cert.pem', keyfile='key.pem')
        context.options |= ssl.OP_NO_COMPRESSION
        return context
    
    def hash_sensitive_data(self, data: str) -> str:
        """Hash sensitive data before storing."""
        return hashlib.sha256(data.encode()).hexdigest()
    
    def rotate_keys(self):
        """Rotate security keys periodically."""
        # Generate new secret key
        new_secret_key = secrets.token_urlsafe(32)
        
        # Re-issue all tokens with new key
        for device_id in self.allowed_devices:
            new_api_key = secrets.token_urlsafe(32)
            self.allowed_devices[device_id]['api_key'] = new_api_key
            
        self.secret_key = new_secret_key
        logger.info("Security keys rotated successfully")
    
    def revoke_device_access(self, device_id: str):
        """Revoke access for a specific device."""
        if device_id in self.allowed_devices:
            del self.allowed_devices[device_id]
            logger.info(f"Access revoked for device {device_id}")
    
    def cleanup_expired_sessions(self):
        """Clean up expired sessions and failed attempts."""
        current_time = datetime.utcnow()
        
        # Clean up failed attempts older than 1 hour
        self.failed_attempts = {
            ip: data for ip, data in self.failed_attempts.items()
            if (current_time - data['first_attempt']).total_seconds() < 3600
        }
        
        # Unblock IPs blocked more than 24 hours ago
        # Implementation depends on how you track blocking time