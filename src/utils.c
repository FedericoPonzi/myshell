#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include "inc/utils.h"

void trim_start(char** l){
    while(isspace(**l)){
        (*l)++;
    }
}

int isNull(void* p){
    if(p == NULL)
    {
        return TRUE;
    }
    return FALSE;
}

int debug = 0;
void logm(char* message, ...){
    if(debug) return;
    int output = LOG_STDERR;
    va_list args;
    FILE *saved = stdout;
    switch(output){
        case LOG_STDERR:
            stdout = stderr;
            break;
        case LOG_FILE:
            stdout = fopen("log.txt", "a");
            break;
    }

    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    if(output == LOG_FILE) {
        fclose(stdout);
    }

    stdout = saved; 
}