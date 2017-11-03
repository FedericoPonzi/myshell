#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>
#include "inc/utils.h"
#include "inc/env.h"
#include "inc/parser.h"
#include "inc/signals_handlers.h"
#include <linux/limits.h>
#include "inc/myshell.h"


void init();
void mainLoop();
char* getLine();
int execute(Command* command);

char cwd[PATH_MAX];

pid_t external_command_pid;


/**
 * Gets a single input line
 */
char* getLine()
{
    char* line = NULL;
    size_t line_len = 0;
    ssize_t read;


    read = getline(&line, &line_len, stdin);
    if(read == -1) {
        return NULL;
    }
    //Removes new line char
    line[strlen(line)-1] = '\0';

    return line;
}


/**
* Executes a command, setting the right environment and eventually forking.
*/
int execute(Command* command)
{
	int toRet = -1;

	//Setup the execution, updating stdout/stdin based on command
    if(command->fun)
    {
        assert(command->fun);
        toRet = command->fun(command->argv);
    }
    else
    {
        logm("Command: %s, args: %s\n", command->name, command->argv[1]);
        //Try search for an external command.
        external_command_pid = fork();
        switch(external_command_pid){
            case -1:
                perror("Fork:"); 
                exit(EXIT_FAILURE);
                break;
            case 0: //child
                execvp(command->name, command->argv);
                printf("%s: command not found\n", command->name);
                exit(127);
                break;
            default: //father
                waitpid(external_command_pid, &toRet, 0);
                toRet = WEXITSTATUS(toRet);
        }
        external_command_pid = NULL;
    }
    free_command(command);
    addEnvInt("?", toRet);
	return toRet;
}

void mainLoop()
{
    char* line;
    Command* command; 
    int exit_code;

    while(1)
    {
        getcwd(cwd, sizeof(cwd));
        printf("%s %% ", cwd); //prompt

        line = getLine();

        if(line == NULL)
        {
            break;
        }

        if (strlen(line) > 0)
        {
            command = parser(line);
            exit_code = execute(command);
            printf("(%d) ", exit_code); //For now, so the compiler don't complains
        }
        free(line);
    }
    exit(EXIT_SUCCESS);
}

void init()
{
    logm("Initializing..");
    initEnv();
    initTokens();
    initSignalHandlers();
}