
import socket
from _thread import *


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

IP_address = '127.0.0.1'

Port = 8080

server.bind((IP_address, Port))

server.listen(100)

list_of_clients = []
list_of_messages = []

def clientthread(conn, addr):
	username = conn.recv(2048).decode('utf-8')

	for x in list_of_messages:
		conn.send(x.encode('utf-8'))
	
	conn.send('\--end--/'.encode('utf-8'))
	print('----<' + username + '> join the chat---')
	broadcast('----<' + username + '> join the chat---', conn)
	while True:
			try:
				message = conn.recv(2048).decode('utf-8')
				if message.__contains__('exit') and len(message) == 5:
					t = "----<" + username + "> left the chat----" 
					print(t)
					broadcast(t, conn)
					add_message(t)
					remove(conn)
					return
				elif message:

					print ("<" + username + "> " + message)

				
					message_to_send = "<" + username + "> " + message
					broadcast(message_to_send, conn)
					add_message(message_to_send)

				else:
					
					remove(conn)
					t = "----<" + username + "> left the chat----"
					print(t)
					add_message(t)
					return

			except:
				continue


def broadcast(message, connection):
	for clients in list_of_clients:
		if clients!=connection:
			try:
				clients.send(message.encode('utf-8'))
			except:
				clients.close()


				remove(clients)

def remove(connection):
	if connection in list_of_clients:
		list_of_clients.remove(connection)

def add_message(message):
	list_of_messages.append(message)

while True:

	conn, addr = server.accept()

	list_of_clients.append(conn)
	start_new_thread(clientthread,(conn,addr))	

conn.close()
server.close()
