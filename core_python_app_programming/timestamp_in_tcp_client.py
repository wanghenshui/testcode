#!/usr/bin/python

from socket import *

HOST = ''
PORT = 21567
BUFSIZE = 1024
ADDR =(HOST,PORT)


tcp_cli_sock = socket(AF_INET,SOCK_STREAM)
tcp_cli_sock.connect(ADDR)

while True:
    data = raw_input('> ')
    if not data:
        break
    tcp_cli_sock.send(data)

    data = tcp_cli_sock.recv(BUFSIZE)

    if not data:
        break
    print data

tcp_cli_sock.close()
