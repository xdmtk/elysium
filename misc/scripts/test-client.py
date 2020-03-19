import socket
import threading

def receive_server_msg():
    while True:
        print(s.recv(4096))

s = socket.socket()
s.connect(('elysium-project.net', 6886))
t = threading.Thread(target=receive_server_msg)
t.start()

while True:
    msg = input()
    s.sendall(bytes(msg, 'utf8'))

