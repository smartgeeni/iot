import Adafruit_DHT
import time
sensor = Adafruit_DHT.DHT11
pin = 4
print("Reading temp...")
try:
	while True:
		humidity,temp = Adafruit_DHT.read_retry(sensor,pin)
		if temp is not None and humidity is not None:
			print(f"Temperature = {temp:.1f}C Humidity = {humidity:.1f}%")
		else:
			print("failed")
		time.sleep(2)
except KeyboardInterrupt:
	print("\nStopped")
