import socket, sys, time
from numbers import Integral
 
def myreverse (a):
    res = []
    for x in range(len(a)):
        res.append(a[x])
    res.reverse()
    return "".join(res)
 
HOST = "10.254.254.100"
PORT = 10000
BUFF_S = 4

conn = socket.socket()
conn.connect((HOST, PORT))
data = (conn.recv(BUFF_S + 1).decode())
pid = int(data[0])
print("pid -> " + str(pid))
print(data[1: ])
conn.send((str(pid) + myreverse(data[1: ])).encode())
conn.close()
