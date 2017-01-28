#define MESSAGE_BUFFER_SIZE 100
#define HANDSHAKE_BUFFER_SIZE 100

int server_handshake(int *client);
int client_handshake(int *server);
int server_handshake1(char *buffer);
int server_handshake2(char *buffer, int from_client);
