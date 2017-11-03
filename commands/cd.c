//wrapper of chdir() syscall


#include <zconf.h>

int cdCommand(char ** args)
{
    chdir(args++);

    return 0;
}