import json
import boto3
import requests
import time
from datetime import datetime
from dateutil import tz
import uuid


TELEGRAM_BOT_TOKEN = '6474929279:AAEAVbJDZO2SBfww1HuRhRgJFnQfTkm9nJA'
TELEGRAM_CHAT_ID = '5630886381'

def send_message_to_telegram(message):
    # URL base de la API de Telegram para enviar mensajes
    telegram_api_url = f'https://api.telegram.org/bot6474929279:AAEAVbJDZO2SBfww1HuRhRgJFnQfTkm9nJA/sendMessage'
    
    # Parámetros del mensaje (chat_id y texto a enviar)
    params = {
        'chat_id': TELEGRAM_CHAT_ID,
        'text': message
    }
    
    # Enviar la solicitud POST a la API de Telegram
    response = requests.post(telegram_api_url, params=params)
    
    # Verificar si la solicitud fue exitosa
    if response.status_code == 200:
        print("Mensaje enviado a Telegram con éxito")
    else:
        print("Error al enviar el mensaje a Telegram")

def process_temperature_humidity_event(event):
    target_timezone = tz.gettz('America/Guatemala')
    tiempo_actual = time.time()
    tiempo_actual_dt = datetime.fromtimestamp(tiempo_actual, target_timezone)
    tiempo_actual_str = tiempo_actual_dt.strftime("%Y-%m-%d %H:%M:%S")
    user_id = str(uuid.uuid4())
    
    temp = event['temperature']
    press = event['pressure']
    alt = event['altitude']