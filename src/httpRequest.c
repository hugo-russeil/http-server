#include "httpRequest.h"
#include <stdio.h>

httpRequest parseRequest(char* buffer){
    httpRequest request;
    sscanf(buffer, "%6s %1023s %s", request.method, request.path, request.param);
    return request;
}