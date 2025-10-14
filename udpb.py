import socket
import Adafruit_DHT

sensor = Adafruit_DHT.DHT11
pin = 4  # GPIO pin

UDP_IP = "0.0.0.0"  # Listen on all interfaces
UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"UDP server listening on port {UDP_PORT}...")

try:
    while True:
        data, addr = sock.recvfrom(1024)  # Receive message
        print(f"Received message from {addr}: {data.decode()}")

        humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

        if humidity is not None and temperature is not None:
            response = f"Temperature={temperature:.1f}C Humidity={humidity:.1f}%"
        else:
            response = "Sensor read failed"

        sock.sendto(response.encode(), addr)  # Send response back

except KeyboardInterrupt:
    print("\nServer stopped.")
finally:
    sock.close()
