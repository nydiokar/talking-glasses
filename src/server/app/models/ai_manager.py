import torch
import whisper
import ollama
from ultralytics import YOLO
import asyncio
import logging
from typing import Optional, Dict, Any

logger = logging.getLogger(__name__)

class AIManager:
    def __init__(self):
        self.whisper_model = None
        self.vision_model = None
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        self.model_cache = {}
        
    async def initialize_models(self):
        """Initialize all AI models."""
        try:
            logger.info("Initializing AI models...")
            
            # Initialize Whisper model
            self.whisper_model = whisper.load_model("small")
            
            # Initialize YOLO model
            self.vision_model = YOLO('yolov8n.pt')
            self.vision_model.to(self.device)
            
            # Verify Ollama is running
            try:
                ollama.pull("mistral")
            except Exception as e:
                logger.error(f"Failed to pull Mistral model: {e}")
            
            logger.info("AI models initialized successfully")
            return True
        except Exception as e:
            logger.error(f"Failed to initialize models: {e}")
            return False
    
    async def process_audio(self, audio_data: bytes) -> Dict[str, Any]:
        """Process audio data and return transcription."""
        try:
            # Save temporary audio file
            with open("temp_audio.wav", "wb") as f:
                f.write(audio_data)
            
            # Transcribe with Whisper
            result = self.whisper_model.transcribe("temp_audio.wav")
            
            # Get response from LLM
            response = await self.get_llm_response(result["text"])
            
            return {
                "transcription": result["text"],
                "response": response
            }
        except Exception as e:
            logger.error(f"Audio processing error: {e}")
            raise
    
    async def process_vision(self, image_data: bytes) -> Dict[str, Any]:
        """Process image data and return detections."""
        try:
            # Save temporary image file
            with open("temp_image.jpg", "wb") as f:
                f.write(image_data)
            
            # Run inference
            results = self.vision_model("temp_image.jpg")
            
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
            logger.error(f"Vision processing error: {e}")
            raise
    
    async def get_llm_response(self, text: str) -> str:
        """Get response from local LLM."""
        try:
            response = ollama.chat(model="mistral", messages=[
                {"role": "user", "content": text}
            ])
            return response["message"]["content"]
        except Exception as e:
            logger.error(f"LLM processing error: {e}")
            return "Sorry, I couldn't process that request."
    
    async def process_message(self, message: str) -> str:
        """Process websocket messages."""
        try:
            response = await self.get_llm_response(message)
            return response
        except Exception as e:
            logger.error(f"Message processing error: {e}")
            return "Error processing message"
    
    async def cleanup(self):
        """Cleanup resources before shutdown."""
        try:
            # Clear CUDA cache if using GPU
            if torch.cuda.is_available():
                torch.cuda.empty_cache()
            
            # Clear any temporary files
            import os
            temp_files = ["temp_audio.wav", "temp_image.jpg"]
            for file in temp_files:
                if os.path.exists(file):
                    os.remove(file)
        except Exception as e:
            logger.error(f"Cleanup error: {e}")
