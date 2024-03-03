#include "requestHandler.h"
#include "httpRequest.h"
#include "httpResponse.h"
#include "fileHandler.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void handleRequest(int sock_fd, char* request){
    httpRequest req = parseRequest(request);
    if (req.method == NULL || req.path == NULL) {
        // Handle parse error
        char* content = "400 Bad Request";
        httpResponse response = createResponse(HTTP_BAD_REQUEST, HTTP_CONTENT_TEXT, content);
        sendResponse(sock_fd, response);
        return;
    }
    httpResponse response;
    if(strcmp(req.method, "GET") == 0){

        if(strncmp(req.path, ECHO_PATH, ECHO_PATH_SIZE) == 0){
            char* content = req.path + 6;
            response = createResponse(HTTP_OK, HTTP_CONTENT_TEXT, content);
        }else if(strncmp(req.path, USER_AGENT_PATH, USER_AGENT_PATH_SIZE) == 0){
            char* user_agent = getUserAgent(request);
            if (user_agent == NULL) {
                char* content = "User-Agent not found";
                response = createResponse(HTTP_OK, HTTP_CONTENT_TEXT, content);
            } else {
                response = createResponse(HTTP_OK, HTTP_CONTENT_TEXT, user_agent);
            }
            free(user_agent);
        }else{
            char* filePath = malloc(strlen(CONTENT_FOLDER) + strlen(req.path) + 1);
            if (filePath == NULL) {
                // Handle malloc failure
                char* content = "500 Internal Server Error";
                httpResponse response = createResponse(HTTP_INTERNAL_SERVER_ERROR, HTTP_CONTENT_TEXT, content);
                sendResponse(sock_fd, response);
                return;
            }
            strcpy(filePath, CONTENT_FOLDER);
            strcat(filePath, req.path);
            if(doesFileExist(filePath) == 1){

                FILE* file = fopen(filePath, "r");
                if (file != NULL) {
                    // Get the file size
                    fseek(file, 0, SEEK_END);
                    long fileSize = ftell(file);
                    rewind(file);

                    // Read the file into a buffer
                    char* buffer = malloc(fileSize + 1);
                    if (buffer == NULL) {
                        // Handle malloc failure
                        char* content = "500 Internal Server Error";
                        response = createResponse(HTTP_INTERNAL_SERVER_ERROR, HTTP_CONTENT_TEXT, content);
                    } else {
                        fread(buffer, 1, fileSize, file);
                        buffer[fileSize] = '\0'; // Null-terminate the buffer

                        response = createResponse(HTTP_OK, extensionToHtmlType(getFileExtension(filePath)), buffer);

                        free(buffer);
                    }
                    fclose(file);
                }else{
                    char* content = "500 Internal Server Error";
                    response = createResponse(HTTP_INTERNAL_SERVER_ERROR, HTTP_CONTENT_TEXT, content);
                }
            }else{
                char* content = "404 Not Found";
                response = createResponse(HTTP_NOT_FOUND, HTTP_CONTENT_TEXT, content);
            }
            free(filePath);
        }
    }else if(strcmp(req.method, "POST") == 0){
        //handle post maybe idk
    }
    sendResponse(sock_fd, response);
}

char* getUserAgent(char* request) {
    char* user_agent_start = strstr(request, "User-Agent: ");
    if (user_agent_start == NULL) {
        return NULL;
    }
    user_agent_start += strlen("User-Agent: "); // Skip past "User-Agent: "

    char* user_agent_end = strchr(user_agent_start, '\n');
    if (user_agent_end == NULL) {
        return NULL;
    }

    size_t user_agent_len = user_agent_end - user_agent_start;
    char* user_agent = malloc(user_agent_len + 1); // +1 for the null terminator
    if (user_agent == NULL) {
        return NULL;
    }

    strncpy(user_agent, user_agent_start, user_agent_len);
    user_agent[user_agent_len] = '\0'; // Null terminate the string

    return user_agent;
}