#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <zconf.h>


int echoCommand(char** args)
{
    *args++;
    while(*args) {
        printf("%s ", *args);
        *args++;
    }
    printf("\n");
    return 0;
}
