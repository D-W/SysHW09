compile:
	gcc client.c -o client
	gcc server.c -o server
	gcc pipe_networking.c -o pipe

run: compile
	./client
	./server
	./pipe
	
clear:
	rm *~