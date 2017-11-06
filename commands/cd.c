#include <zconf.h>
#include <utils.h>
#include <stdio.h>

int cdCommand(char ** args)
{
    *args++;
    int ret = chdir(*args);
    if(ret == -1)
        perror("cd");
    return ret;
}