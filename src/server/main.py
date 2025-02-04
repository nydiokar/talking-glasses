from fastapi import FastAPI, WebSocket, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from app.routers import audio, vision, chat
from app.models.ai_manager import AIManager
from app.security import SecurityManager
import uvicorn
import logging
import ssl

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    filename='ai_glasses_server.log'
)

logger = logging.getLogger(__name__)

app = FastAPI(title="AI Glasses Server")

# Security setup
security_manager = SecurityManager()

# CORS setup - restrict to local network
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # In production, replace with specific IP ranges
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Initialize AI models
ai_manager = AIManager()

# Include routers
app.include_router(audio.router, prefix="/audio", tags=["audio"])
app.include_router(vision.router, prefix="/vision", tags=["vision"])
app.include_router(chat.router, prefix="/chat", tags=["chat"])

@app.on_event("startup")
async def startup_event():
    logger.info("Starting AI Glasses Server")
    await ai_manager.initialize_models()

@app.on_event("shutdown")
async def shutdown_event():
    logger.info("Shutting down AI Glasses Server")
    await ai_manager.cleanup()

@app.get("/health")
async def health_check():
    return {"status": "healthy"}

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    try:
        while True:
            data = await websocket.receive_text()
            # Process the received data
            response = await ai_manager.process_message(data)
            await websocket.send_text(response)
    except Exception as e:
        logger.error(f"WebSocket error: {e}")
    finally:
        await websocket.close()

if __name__ == "__main__":
    # SSL context setup
    ssl_context = ssl.create_default_context(ssl.Purpose.CLIENT_AUTH)
    ssl_context.load_cert_chain('cert.pem', keyfile='key.pem')
    
    # Run server
    uvicorn.run(
        "main:app",
        host="0.0.0.0",
        port=8000,
        ssl_certfile="cert.pem",
        ssl_keyfile="key.pem",
        reload=True
    )