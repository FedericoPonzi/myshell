#ifndef PARSER_H 
#define PARSER_H

typedef struct {
    int (*fun) (char**);
    char* name;
    char** argv;
} Command;

typedef struct token_t{
    char* name;
    int (*fun)(char** );
    struct token_t* next;
}Token;

extern Token** tokens_list;

Command* parser(char* line);
void free_command(Command*);

void addToken(char* name, int (*func)(char**));

void initTokens();
void clearTokens();

#endif
