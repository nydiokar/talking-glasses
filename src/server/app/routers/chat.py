from fastapi import APIRouter, HTTPException, Depends, WebSocket
from typing import Dict, Any
from ..models.ai_manager import AIManager
import logging

logger = logging.getLogger(__name__)
router = APIRouter()

@router.post("/query")
async def process_query(
    query: Dict[str, str],
    ai_manager: AIManager = Depends()
) -> Dict[str, str]:
    """
    Process a text query and return AI response.
    """
    try:
        response = await ai_manager.get_llm_response(query["text"])
        return {"response": response}
    except Exception as e:
        logger.error(f"Error processing query: {e}")
        raise HTTPException(status_code=500, detail=str(e))

@router.websocket("/ws")
async def websocket_endpoint(
    websocket: WebSocket,
    ai_manager: AIManager = Depends()
):
    """
    WebSocket endpoint for real-time chat.
    """
    await websocket.accept()
    try:
        while True:
            data = await websocket.receive_text()
            response = await ai_manager.get_llm_response(data)
            await websocket.send_text(response)
    except Exception as e:
        logger.error(f"WebSocket error: {e}")
    finally:
        await websocket.close()