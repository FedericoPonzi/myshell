#include <stdio.h>
#include <stdarg.h>
#include "inc/utils.h"

#define LOG_STDERR 0
#define LOG_STDOUT 1
#define LOG_FILE 2

int debug = 1;
void logm(char* message, ...){
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