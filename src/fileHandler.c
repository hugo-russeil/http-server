#include "fileHandler.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

int doesFileExist(const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        return 0;
    }
    fclose(file);
    return 1;
}

char* getFileExtension(const char* filename){
    char* dot = strrchr(filename, '.');
    if(!dot || dot == filename){
        return "";
    }
    return dot + 1;
}

//Temporary spaghetti code, to be replaced with hashmap
char* extensionToHtmlType(char* extension){
    if(strcmp(extension, "html") == 0){
        return "text/html";
    }else if(strcmp(extension, "css") == 0){
        return "text/css";
    }else if(strcmp(extension, "js") == 0){
        return "text/javascript";
    }else if(strcmp(extension, "jpg") == 0){
        return "image/jpeg";
    }else if(strcmp(extension, "jpeg") == 0){
        return "image/jpeg";
    }else if(strcmp(extension, "png") == 0){
        return "image/png";
    }else if(strcmp(extension, "gif") == 0){
        return "image/gif";
    }else if(strcmp(extension, "ico") == 0){
        return "image/x-icon";
    }else if(strcmp(extension, "json") == 0){
        return "application/json";
    }else if(strcmp(extension, "pdf") == 0){
        return "application/pdf";
    }else if(strcmp(extension, "xml") == 0){
        return "application/xml";
    }else if(strcmp(extension, "zip") == 0){
        return "application/zip";
    }else if(strcmp(extension, "mp3") == 0){
        return "audio/mpeg";
    }else if(strcmp(extension, "wav") == 0){
        return "audio/wav";
    }else if(strcmp(extension, "mp4") == 0){
        return "video/mp4";
    }else if(strcmp(extension, "webm") == 0){
        return "video/webm";
    }else if(strcmp(extension, "ogg") == 0){
        return "video/ogg";
    }else{
        return "text/plain";
    }
}