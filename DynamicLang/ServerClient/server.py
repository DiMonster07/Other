import threading, datetime, socket, select, os
from io import SEEK_SET
from subprocess import Popen, PIPE
from numbers import Integral
 
HOST = "10.51.16.78"
PORT = 10007
BUFF_S = 5
fw = -1
offset = 0
 
list_keys = []
list_values = []
 
def write_in_place (partscount, text, outfile, num):
    offset_ = (partscount - num - 1)*BUFF_S
    print("Offset: " + str(offset_))
    print(text)
    if offset_ != 0:
        offset_ -= offset
        outfile.seek(offset_, SEEK_SET)
        outfile.write(text)
    else:
        outfile.seek(0, SEEK_SET)
        outfile.write(text)
    return
 
indata = open('test.txt', 'r')
indata.seek(0, os.SEEK_END)
file_size = indata.tell()
print ("File size -> " + str(file_size))
indata.seek(0, os.SEEK_SET)
cout_parts = int(file_size / BUFF_S)
 
offset = BUFF_S - file_size % BUFF_S
if offset != BUFF_S:
    cout_parts += 1
else:
    offset = 0
print ("Offset -> " + str(offset))
 
connected = []
server = socket.socket()
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind((HOST, PORT))
server.listen(cout_parts*2)
connected.append(server)
 
print ("Count parts -> " + str(cout_parts))
out = open('out.txt', 'w')
arr_proc = []
z = 0
c = 0
flag = 0
while not flag:
    read_sockets, a, b = select.select(connected, [], [])
    for sock in read_sockets:
        if sock == server:
            curr_data = indata.read(BUFF_S)
            sockt, addr = server.accept()
            connected.append(sockt)
            list_keys.append(0)
            list_values.append(addr[1])
            print(str(z) + "\n")
            if fw == -1:
                fw = z
            print("Client (%s, %s) connected" % addr)
            sockt.send((str(z) + curr_data).encode())
            z += 1
            c += 1
        else:
            data = sock.recv(BUFF_S + 1).decode()
            id = int(data[0])
            print(str(id))
            print ("Incoming data -> " + data[1: ])
            write_in_place(cout_parts , data[1: ], out, id)
            c += 1
            sock.close()
            connected.remove(sock)
            if c > cout_parts * 2 - 1:
                flag = 1
                print ("End cycle")
out.close()
server.close()