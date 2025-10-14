import socket

UDP_IP = "10.1.22.178"  # Replace with your Pi's IP
UDP_PORT = 5005
MESSAGE = "Request data"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(MESSAGE.encode(), (UDP_IP, UDP_PORT))

data, addr = sock.recvfrom(1024)
print("Received:", data.decode())
