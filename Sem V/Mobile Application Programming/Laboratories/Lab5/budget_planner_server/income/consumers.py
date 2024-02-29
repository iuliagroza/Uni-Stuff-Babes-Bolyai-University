import json
import logging

from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger(__name__)

class IncomeConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        logger.info("WebSocket connected")
        await self.accept()
        await self.channel_layer.group_add('income_updates', self.channel_name)

    async def disconnect(self, close_code):
        logger.info(f"WebSocket disconnected with code: {close_code}")
        pass

    async def send_income_update(self, event):
        logger.info(f"Sending income update: {event}")
        try:
            await self.send(text_data=json.dumps(event['data']))
        except Exception as e:
            logger.error(f"Error sending message: {e}")