#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inc/parser.h"
#include <ctype.h>
#include "inc/utils.h"
#include "inc/commands.h"
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef enum REDIRECTION_E{
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION
} REDIRECTION_E;

Token** tokens_list; //TODO: change to an hashmap

static const char* CONNECTORS[] = {"&&", "||", ";", "|"};
typedef enum CONNECTORS_E{
    AND,
    OR,
    SEMICOLON,
    PIPE
} CONNECTORS_E;
#define CONNECTORS_ECOUNT 4


typedef struct Redirection{
    REDIRECTION_E type;
}Redirection;

char* parse_connector(char** line);

Command* parse_command(char** line);
Redirection* parse_redirection(char** line);

typedef struct Statement{
    Command* command;
    Command* next;
} Statement;

// A statement is a list of commands.
Statement* create_statement(){
    Statement* toRet = calloc(1, sizeof(Statement));
    return toRet;
}

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
    //free(c->name);
    free(c->argv);
    free(c);
}


// Parses a statement
char* statement(char** line){
    Command* command = parse_command(line);
    if(command == NULL)
    {
        //TODO Handle null.
    }
    char* pro = parse_connector(line);
    if(!isNull(pro))
    {
        //TODO: Add to this statement a chain to the next statement.
        //If it's a semicolon, it's cool to return a null command.
    }
}

Token* getTokenFromCommandName(char* name)
{
    Token* it = *tokens_list;
    while(!isNull(it))
    {
        if (strcmp(name, it->name) == 0)
        {
            logm("Match!\n");
            break;
        }

        it = it->next;
    }
    return it;
}

int isa_connector(char* c){
    for(int i = 0; i < CONNECTORS_ECOUNT; i++)
    {
        const char* conn = CONNECTORS[i];
        int flag = 1;
        for(int i = 0; i < MIN(strlen(conn), strlen(c)); i++){
            if(conn[i] != c[i]) {
                flag = 0;
                break;
            }
        }
        if(flag) return 1;
    }
}

/*while isspace(line[i]) and line[i] != \0; # trim
        line[i] = \0;
i++
while line[i] != " " && line[i] != "\0": # command name
i++;
strncpy(line, arg->command_name, i-last_index);
break;
*/
Command * parse_command(char ** line){
    Command* c = create_command();
    char** argv = c->argv;
    logm("Start parsing command...\n");
    // cat file
    trim_start(line);
    if(*line == 0)
    {
        return NULL; //TODO handle no command case.
    }
    int i = 0;
    while(!isspace(*line) && *line != 0)
        i++;
    c->name = malloc(i+1);
    strncpy(c->name, *line, i);

    Token* t = getTokenFromCommandName(c->name);
    c->fun = t != NULL? t->fun : NULL;
    // TODO: parse redirection + add redirection in some way on the struct
    Redirection* r = parse_redirection(line);
    r = parse_redirection(line);
    return c;
}


Redirection* parse_redirection(char** line){
    trim_start(line);
    Redirection* r = NULL;
    if(**line == 0) return NULL;
    if(**line == '<')
    {
        r = calloc(1, sizeof(Redirection));
        r->type = INPUT_REDIRECTION;
    }
    if(**line == '>')
    {
        r = calloc(1, sizeof(Redirection));
        r->type = OUTPUT_REDIRECTION;
    }
    /* TODO: parse file (input/output) of the redirection + retry for other direction */
    return r;
}

char* parse_connector(char** line){
    trim_start(line);


    return NULL;
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

    Token* it = *tokens_list;
    while(!isNull(it))
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
    addToken("exit", &exitCommand);
    logm("Done loading tokens.\n");
}

void clearTokens()
{
    //TODO

}
