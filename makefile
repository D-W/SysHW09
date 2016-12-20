fserver: fserver.o pipe_networking.o
	gcc -o fserver fserver.o pipe_networking.o

server: server.o pipe_networking.o
	gcc -o server server.o pipe_networking.o

client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

fserver.o: fserver.c pipe_networking.h
	gcc -c fserver.c

server: server.c pipe_networking.h
	gcc -c server.c

client: clent.c pipe_networking.h
	gcc -c client.c

