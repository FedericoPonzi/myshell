//
// Created by isaacisback on 15/10/17.
//

#ifndef FIRST_MYSHELL_H
#define FIRST_MYSHELL_H
#include <signal.h>

#define COMMAND_NOT_FOUND 127


extern pid_t external_command_pid;
void init();
void mainLoop();

#endif //FIRST_MYSHELL_H
