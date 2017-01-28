#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "pipe_networking.h"

int server_handshake(int *client) {
    umask(0000);
    //1) Server creates a FIFO (Well Known Pipe)
    mkfifo("wkp", 0644);
    printf("[SERVER] wkp created\n");

    //2) Server waits for a connection (open call)
    int fd = open("wkp", O_RDONLY);
    printf("[SERVER] connection attempt, waiting for client\n");

    //-------

    //6) Server receives client’s message and removes the WKP
    char buf[MESSAGE_BUFFER_SIZE];
    read(fd, buf, sizeof(buf));
    printf("received client's message\n");
    close(fd);
    remove("wkp");
    printf("[SERVER] wkp removed\n");

    //7) Server connects to client FIFO, sending an initial acknowledgement message
    int fd2 = open(buf, O_WRONLY);
    char message = "hey";
    write(fd2, message, sizeof(message));
    printf("[SERVER] sent message\n");
    return fd2;
}



int client_handshake(int *server) {
    umask(0000);
    //3) Client creates a “private” FIFO
    mkfifo("privp",0644);
    printf("[CLIENT]: private pipe made\n");

    //4) Client connects to server and send the private FIFO name (write)
    int pd = open("wkp", O_WRONLY);
    write(pd, "privp", sizeof("privp"));
    printf("[CLIENT] sent message\n");

    //5) Client waits for a message from the server (open call)
    int pd2 = open("privp", O_RDONLY);

    //-------

    //8) Client receives server’s message, removes its private FIFO
    char buf[MESSAGE_BUFFER_SIZE];
    read(pd2, buf, sizeof(buf));
    printf("[CLIENT]: got message: %s\n",buf);
    close(pd2);
    remove("privp");
    printf("[CLIENT]: removed pipe\n");


    //9) Client sends a confirmation message to the server
    char message = "hi confirmation";
    write(pd2,message,sizeof(message));
    return pd2;
}

int server_handshake1(char *buffer) {
    umask(0000);

    //1) Server creates a FIFO (Well Known Pipe)
    mkfifo("wkp", 0644);
    printf("[SERVER] wkp created\n");

    //2) Server waits for a connection (open call)
    int fd = open("wkp", O_RDONLY);
    printf("[SERVER] connection attempt, waiting for client\n");

    //6) Server receives client’s message and removes the WKP
    read(fd, buffer, sizeof(buffer));
    printf("received client's message\n");
    close(fd);
    remove("wkp");
    printf("[SERVER] wkp removed\n");

    return fd;
}

int server_handshake2(char *buffer, int from_client) {
    //7) Server connects to client FIFO, sending an initial acknowledgement message
    int fd2 = open(buffer, O_WRONLY);
    char message = "hey";
    write(fd2, message, sizeof(message));
    printf("[SERVER] sent message\n");
    read(from_client, buffer, sizeof(buffer));
    printf("[SERVER] recieved message: %s\n", buffer);
    remove("wkp");
    return fd2;
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
