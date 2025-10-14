import Adafruit_DHT
import time
import requests

sensor = Adafruit_DHT.DHT11
pin = 4  # GPIO pin connected to DHT11 data

THINGSPEAK_API_KEY = "LPGYE0MYPEC0F4WC"  # Replace with your ThingSpeak Write API Key
THINGSPEAK_URL = "https://api.thingspeak.com/update"

def send_to_thingspeak(temp, humidity):
    payload = {
        'api_key': THINGSPEAK_API_KEY,
        'field1': temp,
        'field2': humidity
    }
    try:
        response = requests.post(THINGSPEAK_URL, data=payload, timeout=5)
        print("Sent to ThingSpeak. Response code:", response.status_code)
    except requests.RequestException as e:
        print("Failed to send data:", e)

try:
    while True:
        humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
        if humidity is not None and temperature is not None:
            print("Temperature: {:.1f}C, Humidity: {:.1f}%".format(temperature, humidity))
            send_to_thingspeak(temperature, humidity)
        else:
            print("Failed to read sensor data.")
        time.sleep(15)  # ThingSpeak free-tier rate limit
except KeyboardInterrupt:
    print("\nProgram stopped by user.")

