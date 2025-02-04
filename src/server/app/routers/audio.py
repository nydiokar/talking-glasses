from fastapi import APIRouter, UploadFile, File, HTTPException, Depends
from typing import Dict, Any
from ..models.ai_manager import AIManager
import logging

logger = logging.getLogger(__name__)
router = APIRouter()

@router.post("/process")
async def process_audio(
    audio_file: UploadFile = File(...),
    ai_manager: AIManager = Depends()
) -> Dict[str, Any]:
    """
    Process audio file and return transcription with AI response.
    """
    try:
        content = await audio_file.read()
        result = await ai_manager.process_audio(content)
        return result
    except Exception as e:
        logger.error(f"Error processing audio: {e}")
        raise HTTPException(status_code=500, detail=str(e))

@router.post("/transcribe")
async def transcribe_only(
    audio_file: UploadFile = File(...),
    ai_manager: AIManager = Depends()
) -> Dict[str, str]:
    """
    Only transcribe audio without AI processing.
    """
    try:
        content = await audio_file.read()
        result = await ai_manager.process_audio(content)
        return {"transcription": result["transcription"]}
    except Exception as e:
        logger.error(f"Error transcribing audio: {e}")
        raise HTTPException(status_code=500, detail=str(e))