//
// Created by isaacisback on 15/10/17.
//

#include <unistd.h>
#include "sleep.h"
#include <inttypes.h>
#include <errno.h>

int waitCommand(char** args)
{
    *args++;
    if(*args){
        //uintmax_t num = strtoumax(s, NULL, 10);
        //if (num == UINTMAX_MAX && errno == ERANGE)
            return -1;
    }
    sleep(0);
    return 0;
}
