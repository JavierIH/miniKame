import socket

s = socket.socket()
s.connect(("192.168.1.3", 80))
s.send("W")
s.close()
