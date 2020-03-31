import zmq


context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect("tcp://localhost:5555")
socket.setsockopt(zmq.SUBSCRIBE,'10001'.encode('utf-8')) 
socket.setsockopt(zmq.SUBSCRIBE,'10002'.encode('utf-8')) 
while True:
    response = socket.recv().decode('utf-8');
    print("response: %s" % response)
