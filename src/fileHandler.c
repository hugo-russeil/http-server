#include "fileHandler.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <glib.h>

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

GHashTable* createExtensionToHtmlTypeMap() {
    GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(map, "txt", "text/plain");
    g_hash_table_insert(map, "htm", "text/html");
    g_hash_table_insert(map, "html", "text/html");
    g_hash_table_insert(map, "css", "text/css");
    g_hash_table_insert(map, "js", "text/javascript");
    g_hash_table_insert(map, "jpg", "image/jpeg");
    g_hash_table_insert(map, "jpeg", "image/jpeg");
    g_hash_table_insert(map, "png", "image/png");
    g_hash_table_insert(map, "gif", "image/gif");
    g_hash_table_insert(map, "ico", "image/x-icon");
    g_hash_table_insert(map, "json", "application/json");
    g_hash_table_insert(map, "pdf", "application/pdf");
    g_hash_table_insert(map, "xml", "application/xml");
    g_hash_table_insert(map, "zip", "application/zip");
    g_hash_table_insert(map, "mp3", "audio/mpeg");
    g_hash_table_insert(map, "wav", "audio/wav");
    g_hash_table_insert(map, "mp4", "video/mp4");
    g_hash_table_insert(map, "webm", "video/webm");
    g_hash_table_insert(map, "ogg", "video/ogg");

    return map;
}

char* extensionToHtmlType(char* extension) {
    static GHashTable* map = NULL;
    if (map == NULL) {
        map = createExtensionToHtmlTypeMap();
    }

    char* htmlType = g_hash_table_lookup(map, extension);
    if (htmlType == NULL) {
        return "text/plain";
    }

    return htmlType;
}
