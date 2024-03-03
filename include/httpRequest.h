#define MAX_METHOD_SIZE 7 // "DELETE" + '\0'
#define MAX_PATH_SIZE 1024
#define MAX_PARAM_SIZE 128

typedef struct {
    char method[MAX_METHOD_SIZE];
    char path[MAX_PATH_SIZE];
    char param[MAX_PARAM_SIZE];
} httpRequest;

httpRequest parseRequest(char* buffer);