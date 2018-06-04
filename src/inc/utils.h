#ifndef UTILS_H
#define UTILS_H
#define TRUE 1
#define FALSE 0

#define LOG_STDERR 0
#define LOG_STDOUT 1
#define LOG_FILE 2
void logm(char*, ...);
void trim_start(char** l);
int isNull(void* p);
#endif
