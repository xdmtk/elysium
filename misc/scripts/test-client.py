import socket

s = socket.socket()
s.connect(('127.0.0.1', 6692))
while True:
    msg = input()
    s.sendall(bytes(msg, 'utf8'))
    print(s.recv(4096))

