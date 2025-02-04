from fastapi import APIRouter, UploadFile, File, HTTPException, Depends
from typing import Dict, Any
from ..models.ai_manager import AIManager
import logging

logger = logging.getLogger(__name__)
router = APIRouter()

@router.post("/process")
async def process_image(
    image_file: UploadFile = File(...),
    ai_manager: AIManager = Depends()
) -> Dict[str, Any]:
    """
    Process image file and return detections.
    """
    try:
        content = await image_file.read()
        result = await ai_manager.process_vision(content)
        return result
    except Exception as e:
        logger.error(f"Error processing image: {e}")
        raise HTTPException(status_code=500, detail=str(e))

@router.post("/describe")
async def describe_image(
    image_file: UploadFile = File(...),
    ai_manager: AIManager = Depends()
) -> Dict[str, str]:
    """
    Generate natural language description of image.
    """
    try:
        content = await image_file.read()
        detections = await ai_manager.process_vision(content)
        
        # Create natural language description from detections
        if detections["detections"]:
            objects = [f"{d['class']} ({d['confidence']:.2f}%)" 
                      for d in detections["detections"]]
            description = f"I can see: {', '.join(objects)}"
        else:
            description = "I don't see any recognizable objects in this image."
        
        return {"description": description}
    except Exception as e:
        logger.error(f"Error describing image: {e}")
        raise HTTPException(status_code=500, detail=str(e))