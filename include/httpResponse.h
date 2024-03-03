#define MAX_STATUS_SIZE 128
#define MAX_CONTENT_TYPE_SIZE 128
#define MAX_CONTENT_LENGTH_SIZE 32
#define DEFAULT_BODY_SIZE 2048

typedef struct {
    char status[MAX_STATUS_SIZE];
    char contentType[MAX_CONTENT_TYPE_SIZE];
    char contentLength[MAX_CONTENT_LENGTH_SIZE];
    char* body;
} httpResponse;


httpResponse createResponse(char* status, char* contentType, char* body);
void sendResponse(int sock_fd, httpResponse response);