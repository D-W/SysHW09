#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "pipe_networking.h"

#define MESSAGE_BUFFER_SIZE = 100;

int server_handshake(int *client) {
    //1) Server creates a FIFO (Well Known Pipe)
    mkfifo("wkp", 0644);
    printf("[SERVER] wkp created\n");

    //2) Server waits for a connection (open call)
    char buf[MESSAGE_BUFFER_SIZE];
    int fd = open("wkp", O_RDONLY);
    printf("[SERVER] connection attempt, waiting for client\n");

    //-------

    //6) Server receives client’s message and removes the WKP
    read(fd, buf, sizeof(buf));
    printf("received client's message: %s\n", );
    close(fd);
    remove("wkp");
    printf("[SERVER] wkp removed\n");

    //7) Server connects to client FIFO, sending an initial acknowledgement message
    int fd2 = open("buf, O_WRONLY");
    char message = "heyo";
    write(fd2, message, sizeof(message));
    printf("[SERVER] sent message")
    return fd2;

}



int client_handshake(int *server) {
    //3) Client creates a “private” FIFO
    char note = (char *)getpid();
    mkfifo(note,0644);
    printf("[CLIENT]: private pipe made");

    //4) Client connects to server and send the private FIFO name (write)
    int pd = open("wkp", O_WRONLY);
    write(pd, note, sizeof(note));
    printf("[CLIENT] sent message"); 


    //5) Client waits for a message from the server (open call)
    int pd2 = open(note, O_RDONLY);

    //-------

    //8) Client receives server’s message, removes its private FIFO
    char buf[MESSAGE_BUFFER_SIZE];
    read(pd2, buf, sizeof(buf));
    printf("[CLIENT]: got message: %s",buf);

    close(pd2);
    printf("[CLIENT]: removed pipe");


    //9) Client sends a confirmation message to the server
    char message = "hi confirmation";
    write(pd2,message,sizeof(message));
    return pd2;



}



/*
Basic Handshake Procedure:
		1) Server creates a FIFO (Well Known Pipe)
		2) Server waits for a connection (open call)
		3) Client creates a “private” FIFO
		4) Client connects to server and send the private FIFO name (write)
		5) Client waits for a message from the server (open call)
		6) Server receives client’s message and removes the WKP
		7) Server connects to client FIFO, sending an initial acknowledgement message
		8) Client receives server’s message, removes its private FIFO
		9) Client sends a confirmation message to the server
*/
