import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("172.30.113.134",7777))
s.listen(5)
cs,addr=s.accept()
b=cs.recv(10)
print(b)
cs.send(b"asdfs")
cs.close()