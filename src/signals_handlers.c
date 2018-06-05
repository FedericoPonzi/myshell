//
// Created by isaacisback on 15/10/17.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "inc/utils.h"
#include "inc/signals_handlers.h"
#include "inc/myshell.h"

void handleSIGINT(){
    logm("* SIGINT TRIGGERED.\n");
    logm("pid: %d", external_command_pid);
    if(external_command_pid)
        kill(external_command_pid, SIGINT);
}
void signalsHandler(int signo)
{
    switch(signo){
        case SIGINT:
            handleSIGINT();
            break;
        default:
            return;
    }
}

void initSignalHandlers()
{
    struct sigaction sa;
    logm("Installing signal handlers...\n");

    sa.sa_handler = &signalsHandler;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error: cannot handle SIGINT"); // Should not happen
    }

    logm("Done setup signal handlers\n");
}
