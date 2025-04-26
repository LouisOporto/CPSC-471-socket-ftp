SRV_OBJ = ftp_server.cpp
CLI_OBJ = ftp_client.cpp
CC = g++
SRV_NAME = -o ftp_server
CLI_NAME = -o ftp_client
all: server client

server:
	$(CC) $(SRV_OBJ) $(SRV_NAME)

client: 
	$(CC) $(CLI_OBJ) $(CLI_NAME)

clean:
	test -n ftp_server && rm -rf ftp_server
	test -n ftp_client && rm -rf ftp_client