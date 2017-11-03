//
// Created by isaacisback on 15/10/17.
//

#include <stdio.h>
#include <signal.h>
#include <utils.h>

#include "signals_handlers.h"
#include "myshell.h"

void sigInt(){
    logm("* SIGINT TRIGGERED.\n");
    if(external_command_pid)
        kill(external_command_pid, SIGINT);
}
void signalsHandler(int signo){
    switch(signo){
        case SIGINT:
            sigInt();
            break;
        default:
            return;
    }
}

void initSignalHandlers()
{
    logm("Installing signal handlers...\n");
    if (signal(SIGINT, signalsHandler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    logm("Done setup signal handlers\n");
}
