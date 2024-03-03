#include "httpResponse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CRLF "\r\n"

httpResponse createResponse(char* status, char* contentType, char* body){
    httpResponse response;
    response.body = malloc(strlen(body) + 1);
    strcpy(response.status, status);
    strcpy(response.contentType, contentType);
    strcpy(response.body, body);
    sprintf(response.contentLength, "%ld", strlen(body));
    return response;
}

void sendResponse(int sock_fd, httpResponse response){
    // Header
    write(sock_fd, response.status, strlen(response.status));
    write(sock_fd, "Content-Type: ", strlen("Content-Type: "));
    write(sock_fd, response.contentType, strlen(response.contentType));
    write(sock_fd, CRLF, strlen(CRLF));
    write(sock_fd, "Content-Length: ", strlen("Content-Length: "));
    write(sock_fd, response.contentLength, strlen(response.contentLength));
    write(sock_fd, CRLF, strlen(CRLF));
    write(sock_fd, CRLF, strlen(CRLF));// Second CRLF to indicate end of header

    // Body
    write(sock_fd, response.body, strlen(response.body));

    free(response.body);
}