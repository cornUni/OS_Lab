
import socket
import select
import sys

username = input("username: ")
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_address = '127.0.0.1'
Port = 8080
server.connect((IP_address, Port))
server.send(username.encode('utf-8'))

history = []

while True:
	x = server.recv(2048).decode('utf-8')
	if x.__contains__('\--end--/'):
		break
	history.append(x)

for x in history:
	print(x , end='\n\n')

del history

while True:

	
	sockets_list = [sys.stdin, server]


	read_sockets,write_socket, error_socket = select.select(sockets_list,[],[])

	for socks in read_sockets:
		if socks == server:
			message = socks.recv(2048).decode('utf-8')
			print (message)
		else:
			message = sys.stdin.readline()
			if message.__contains__('exit') and len(message) == 5:
				server.send(message.encode('utf-8'))
				server.close()
				sys.exit(0)
			server.send(message.encode('utf-8'))
			sys.stdout.write("<You>")
			sys.stdout.write(message)
			sys.stdout.flush()
server.close()
