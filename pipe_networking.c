#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int MESSAGE_BUFFER_SIZE = 50;

int server_handshake(int *i) {
    //1) Server creates a FIFO (Well Known Pipe)
    //2) Server waits for a connection (open call)
    mkfifo("atob", 0644);
    int fd = open("atob", O_RDONLY);

    //6) Server receives client’s message and removes the WKP
    char buf[50];
    read(fd, buf, sizeof(buf));
    //7) Server connects to client FIFO, sending an initial acknowledgement message
    close(fd);
    write(i, buf, sizeof(buf));

}

int client_handshake(int *i) {
    //3) Client creates a “private” FIFO
    //4) Client connects to server and send the private FIFO name (write)
    mkfifo("btoa", 044);
    int fd = open("btoa", O_WRONLY);
    write(i, "btoa", 4);
    char buf[50];
    write(fd, buf, sizeof(buf));
    //8) Client receives server’s message, removes its private FIFO
    //9) Client sends a confirmation message to the server
    read(i, buf, sizeof(buf));



}

int main() {
    //1) Server creates a FIFO (Well Known Pipe)
    //2) Server waits for a connection (open call)
    mkfifo("atob", 0644);
    return 0;
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
