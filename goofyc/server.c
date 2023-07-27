#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// The port number to use for the server
#define PORT 8080

int main(int argc, char *argv[])
{
    // Create a socket for the server
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Bind the socket to a local address and port
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // Listen for incoming connections
    listen(server_socket, 5);

    // Accept incoming connections
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_len);

    // Send a simple HTTP response to the client
    char *response = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>\r\n";
    send(client_socket, response, strlen(response), 0);

    // Close the client and server sockets
    close(client_socket);
    close(server_socket);

    return 0;
}

