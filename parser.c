#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <parser.h>
#include <cd.h>
#include "inc/utils.h"
#include "commands/inc/help.h"
#include "commands/inc/echo.h"
#include "commands/inc/clear.h"

Token** tokens_list;


Command* create_command()
{
    Command* c = malloc(sizeof(Command)); //TODO: to free
    c->fun = NULL;
    c->name = NULL;
    c->argv = malloc(sizeof(char*)*64);
    return c;
}

void free_command(Command* c)
{
    free(c->argv);
    free(c);
}


/**
 * Process the line. Lexer + parser.
 */
Command* parser(char* line)
{
    Command* c = create_command();
    char** argv = c->argv;
    logm("Start parsing command...\n");

    while (*line != '\0') {
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';
        *argv++ = line;
        while (*line != '\0' && *line != ' ' &&
               *line != '\t' && *line != '\n')
            line++;
    }
    *argv = '\0';
    if(strlen(*c->argv) == 0)
    {

    }
    Token* it = *tokens_list;
    while(it != NULL)
    {
        logm("Tok: %s, comando: %s\n", *c->argv, it->name);

        if (strcmp(*c->argv, it->name) == 0)
        {
                logm("Match!\n");
                break;
        }
        
        it = it->next;
    }

    if(it == NULL)
    {
        logm("Command not found. External program\n");

        //External command name
        c->name = c->argv[0];
    }
    else
    {
        // Internal shell function
        c->fun = it->fun;
    }
    return c;
}

/**
 * Add a command to the lists of available commands.
 */
void addToken(char* name, int (*func) (char**))
{    
    Token* t = malloc(sizeof(Token));
    //I to this because of possible future extension (e.g. UDF)
    char* n = strdup(name);
    t->name = n;
    t->fun = func;
    t->next = NULL;
    if(*tokens_list)
    {
        t->next= *tokens_list;
    }
    *tokens_list = t;
}

/**
 * Init of the commands list. Add new commands there!
 */
void initTokens(){
    //Clear:
    logm("Init tokens...\n");
    tokens_list = malloc(sizeof(Token**));
    addToken("clear", &clearCommand);
    addToken("echo", &echoCommand);
    addToken("help", &helpCommand);
    addToken("cd", &cdCommand);
    logm("Done loading tokens.\n");
}

void clearTokens()
{
    //TODO

}
