# Server Setup and AI Configuration Guide

## 1. Environment Setup

### Required Software Installation
```bash
# Core dependencies
pip install fastapi uvicorn
pip install numpy pandas
pip install torch torchvision
pip install whisper
pip install ultralytics
pip install python-multipart
pip install pydantic

# Install Ollama for local LLM
winget install Ollama
```

### Directory Structure Setup
```bash
glasses-ai/
├── server/
│   ├── main.py
│   ├── config.py
│   ├── routes/
│   │   ├── __init__.py
│   │   ├── audio.py
│   │   ├── vision.py
│   │   └── chat.py
│   ├── models/
│   │   └── __init__.py
│   └── utils/
│       ├── __init__.py
│       └── audio_processing.py
```

## 2. Server Implementation

### Main Server (main.py)
```python
from fastapi import FastAPI, WebSocket
from fastapi.middleware.cors import CORSMiddleware
import whisper
import ollama
from ultralytics import YOLO
import asyncio

app = FastAPI()

# CORS setup for local development
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Initialize AI models
whisper_model = whisper.load_model("small")
vision_model = YOLO('yolov8n.pt')

@app.on_event("startup")
async def startup_event():
    # Warm up models
    print("Initializing AI models...")
    
@app.get("/health")
async def health_check():
    return {"status": "healthy"}

# Audio processing endpoint
@app.post("/process-audio/")
async def process_audio(audio_file: bytes):
    try:
        # Save temporary audio file
        with open("temp.wav", "wb") as f:
            f.write(audio_file)
        
        # Process with Whisper
        result = whisper_model.transcribe("temp.wav")
        
        # Get AI response
        response = ollama.chat(model="mistral", 
                             messages=[{"role": "user", 
                                      "content": result["text"]}])
        
        return {
            "transcription": result["text"],
            "response": response["message"]["content"]
        }
    except Exception as e:
        return {"error": str(e)}

# Vision processing endpoint
@app.post("/process-vision/")
async def process_vision(image_file: bytes):
    try:
        # Save temporary image file
        with open("temp.jpg", "wb") as f:
            f.write(image_file)
        
        # Run inference
        results = vision_model("temp.jpg")
        
        # Process results
        detections = []
        for r in results:
            for box in r.boxes:
                detection = {
                    "class": r.names[int(box.cls)],
                    "confidence": float(box.conf),
                    "bbox": box.xyxy[0].tolist()
                }
                detections.append(detection)
        
        return {"detections": detections}
    except Exception as e:
        return {"error": str(e)}

# WebSocket for real-time communication
@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    try:
        while True:
            data = await websocket.receive_text()
            response = ollama.chat(model="mistral", 
                                 messages=[{"role": "user", 
                                          "content": data}])
            await websocket.send_text(response["message"]["content"])
    except Exception as e:
        print(f"WebSocket error: {e}")
    finally:
        await websocket.close()

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000, ssl_keyfile="key.pem", 
                ssl_certfile="cert.pem")
```

### Configuration (config.py)
```python
from pydantic import BaseSettings

class Settings(BaseSettings):
    # Server settings
    HOST: str = "0.0.0.0"
    PORT: int = 8000
    DEBUG: bool = False
    
    # AI Model settings
    WHISPER_MODEL: str = "small"
    YOLO_MODEL: str = "yolov8n.pt"
    LLM_MODEL: str = "mistral"
    
    # Security
    SSL_KEYFILE: str = "key.pem"
    SSL_CERTFILE: str = "cert.pem"
    
    # Audio processing
    AUDIO_SAMPLE_RATE: int = 16000
    MAX_AUDIO_DURATION: int = 30  # seconds
    
    # Vision processing
    IMAGE_SIZE: tuple = (640, 640)
    CONFIDENCE_THRESHOLD: float = 0.5
    
    class Config:
        env_file = ".env"

settings = Settings()
```

## 3. Model Management

### Local LLM Setup
```bash
# Pull and run Mistral model
ollama pull mistral
ollama run mistral

# Test the model
curl http://localhost:11434/api/generate -d '{
  "model": "mistral",
  "prompt": "Tell me a joke"
}'
```

### Vision Model Setup
```python
# Download and cache YOLO model
from ultralytics import YOLO
model = YOLO('yolov8n.pt')
model.to('cuda')  # Move to GPU
```

## 4. Performance Optimization

### GPU Acceleration
```python
import torch

def setup_gpu():
    if torch.cuda.is_available():
        torch.backends.cudnn.benchmark = True
        torch.backends.cuda.matmul.allow_tf32 = True
        torch.backends.cudnn.allow_tf32 = True
    return torch.cuda.is_available()

def optimize_model_inference():
    torch.set_grad_enabled(False)
    torch.inference_mode(True)
```

### Memory Management
```python
class MemoryManager:
    def __init__(self):
        self.cached_responses = {}
        self.max_cache_size = 1000
    
    def clear_cache(self):
        torch.cuda.empty_cache()
        self.cached_responses.clear()
    
    @torch.inference_mode()
    def run_inference(self, model, input_data):
        # Implementation for optimized inference
        pass
```

## 5. Testing Server Setup

```python
from fastapi.testclient import TestClient
from main import app

client = TestClient(app)

def test_health_check():
    response = client.get("/health")
    assert response.status_code == 200
    assert response.json() == {"status": "healthy"}

def test_audio_processing():
    with open("test.wav", "rb") as f:
        response = client.post("/process-audio/", files={"file": f})
    assert response.status_code == 200
    assert "transcription" in response.json()

def test_vision_processing():
    with open("test.jpg", "rb") as f:
        response = client.post("/process-vision/", files={"file": f})
    assert response.status_code == 200
    assert "detections" in response.json()
```

## 6. Monitoring and Logging

```python
import logging
from logging.handlers import RotatingFileHandler

def setup_logging():
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        handlers=[
            RotatingFileHandler(
                'server.log',
                maxBytes=10000000,
                backupCount=5
            ),
            logging.StreamHandler()
        ]
    )
```

## 7. Running the Server

### Development
```bash
uvicorn main:app --reload --host 0.0.0.0 --port 8000
```

### Production
```bash
uvicorn main:app --host 0.0.0.0 --port 8000 --workers 4 --ssl-keyfile key.pem --ssl-certfile cert.pem
```

## 8. Troubleshooting Guide

1. Model Loading Issues:
   - Check GPU memory usage
   - Verify CUDA installation
   - Check model checksums

2. Performance Issues:
   - Monitor GPU utilization
   - Check network latency
   - Verify memory usage

3. Connection Issues:
   - Check SSL certificates
   - Verify network settings
   - Test WebSocket connection