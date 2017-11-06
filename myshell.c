#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/utils.h"
#include "inc/env.h"
#include "inc/parser.h"
#include "inc/signals_handlers.h"
#include <linux/limits.h>
#include "inc/myshell.h"


void init();
void mainLoop();
char* getLine();
unsigned execute(Command* command);

char cwd[PATH_MAX];

pid_t external_command_pid;


/**
 * Gets a single input line
 */
char* getLine()
{
    getcwd(cwd, PATH_MAX); //TODO: add % at the end.
    const char* PROMPT_APPEND = " % ";
    char* prompt = calloc(strlen(cwd) + strlen(PROMPT_APPEND), sizeof(char));
    strcat(prompt, cwd);
    strcat(prompt, PROMPT_APPEND);
    char* line = readline(prompt);
    add_history(line);
    free(prompt);
    return line;
}


/**
* Executes a command, setting the right environment and eventually forking.
*/
unsigned execute(Command* command)
{
    int toRet = 1;

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
	return toRet > 0 ? toRet : -toRet;
}

void mainLoop()
{
    char* line;
    Command* command; 
    int exit_code;

    while(1)
    {
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
    free(line);
    exit(EXIT_SUCCESS);
}

void init()
{
    logm("Initializing..");
    initEnv();
    initTokens();
    initSignalHandlers();
}