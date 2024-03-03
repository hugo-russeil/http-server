#include "httpRequest.h"
#include "httpResponse.h"
#include "requestHandler.h"
#include "fileHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define HTTP_CONTENT_TEXT "text/plain"
#define HTTP_CONTENT_HTML "text/html"

#define HTTP_OK "HTTP/1.1 200 OK\r\n"
#define HTTP_CREATED "HTTP/1.1 201 Created\r\n"
#define HTTP_BAD_REQUEST "HTTP/1.1 400 Bad Request\r\n"
#define HTTP_NOT_FOUND "HTTP/1.1 404 Not Found\r\n"
#define HTTP_INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\r\n"
#define CRLF "\r\n"

#define ECHO_PATH "/echo/"
#define ECHO_PATH_SIZE 6

#define USER_AGENT_PATH "/user-agent"
#define USER_AGENT_PATH_SIZE 11

#define CONTENT_FOLDER "../content/"

int main() {
	char buffer[1024];
	char method[16], path[1024], protocol[16];
	// Disable output buffering
	setbuf(stdout, NULL);
	
	int server_fd, client_addr_len;
	struct sockaddr_in client_addr;
	
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		printf("Socket creation failed: %s...\n", strerror(errno));
		return 1;
	}

	int reuse = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
		printf("SO_REUSEPORT failed: %s \n", strerror(errno));
		return 1;
	}
	
	struct sockaddr_in serv_addr = { .sin_family = AF_INET ,
									 .sin_port = htons(8080),
									 .sin_addr = { htonl(INADDR_ANY) },
									};
	
	if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
		printf("Bind failed: %s \n", strerror(errno));
		return 1;
	}
	
	int connection_backlog = 5;
	if (listen(server_fd, connection_backlog) != 0) {
		printf("Listen failed: %s \n", strerror(errno));
		return 1;
	}
	
	printf("Waiting for a client to connect...\n");
	client_addr_len = sizeof(client_addr);
	
	while(1){	
		int sock_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_len);

		pid_t pid = fork();
		if(pid == -1){
			printf("Fork failed: %s \n", strerror(errno));
			return 1;
		}

		if(pid == 0){
			close(server_fd);
			read(sock_fd, buffer, 1024);
			buffer[sizeof(buffer) - 1] = '\0';// Ensure null-terminated string (segfault otherwise)
			
			handleRequest(sock_fd, buffer);

			printf("Client connected");
			close(sock_fd);
			exit(0);
		}else{
			close(sock_fd);
		}	
	}
	close(server_fd);

	return 0;
}
