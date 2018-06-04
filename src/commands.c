#include <zconf.h>
#include <stdio.h>
#include "inc/commands.h"
#include <stdlib.h>

int cdCommand(char **args) {
    *args++;
    int ret = chdir(*args);
    if (ret == -1)
        perror("cd");
    return ret;
}



int clearCommand(char **args) {
    printf("\033[2J"); /*clear screen*/
    printf("\033[1;1H"); /*put at upper left*/

    return 0;
}


int echoCommand(char **args) {
    *args++;
    while (*args) {
        printf("%s ", *args);
        *args++;
    }
    printf("\n");
    return 0;
}


int exitCommand(char **args) {
    //TODO: parse args for integer exit value.
    exit(0);
}


int helpCommand(char **args) {
    printf("This is a tiny but pretty shell, made for fun.\nCommands available:\n\
 * help - print this help\n\
 * cd [directory] - changes the working directory to directory\n\
 * echo [text|variable] - prints out a string or a variable\n\
 * program - executes a program, searching in PATH (env variable)\n");
    return 0;
}


int waitCommand(char **args) {
    *args++;
    if (*args) {
        //uintmax_t num = strtoumax(s, NULL, 10);
        //if (num == UINTMAX_MAX && errno == ERANGE)
        return -1;
    }
    sleep(0);
    return 0;
}
