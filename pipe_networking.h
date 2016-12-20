#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "pipe_networking.h"

int server_handshake(int *client);
int client_handshake(int *server);