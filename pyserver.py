import zmq
import time
import sys
context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5555")

while True:
    msg = input("abc:").strip()
    if msg == 'b':
        sys.exit()
    socket.send(msg.encode('utf-8'))
    time.sleep(1)