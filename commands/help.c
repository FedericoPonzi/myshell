#include <stdio.h>
#include "inc/help.h"

int helpCommand(char** args)
{
    printf("This is a tiny but pretty shell, made for fun.\nCommands available:\n\
 * help - print this help\n\
 * cd [directory] - changes the working directory to directory\n\
 * echo [text|variable] - prints out a string or a variable\n\
 * program - executes a program, searching in PATH (env variable)\n");
    return 0;
}
