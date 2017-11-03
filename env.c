#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/env.h"

Env **environment;
/**
 * This sould be a K-V hashmap. I will rewrite it someday (maybe)
 */


/**
 * Init the envorionment
 */
void initEnv()
{   
    environment = calloc('\0', sizeof(Env**));
    addEnv("shell", "path/myshell");
}

Env* createVar(char *k, char* v){
    Env* new = calloc('\0', sizeof(Env));
    new->k = k;
    new->v = v;
    return new;
}

/**
 * Adds an element to the internal environment
 * Updates k if it is already present
 */
void addEnv(char* k, char* v)
{
    char* copy = malloc(strlen(k) + 1);
    strcpy(copy, k);
    Env** temp = environment;

    while(*temp != NULL && (strcmp((*temp)->k, k) != 0)) {
        temp = &((*temp)->next);
    }
    if(*temp != NULL){
        (*temp)->v = v;
        return;
    }
    *temp = createVar(k, v);
}

void addEnvInt(char* k, int v)
{
    char* toStr = malloc(21); //TODO: Fix this to a minimum required length
    sprintf(toStr, "%d", v);
    addEnv( k, toStr);
}

/**
 * For debugging
 */
void showEnv()
{
    Env *it = *environment;
    printf("Show environment:\n");
    while (it != NULL)
    {
        printf("%s: %s\n", it->k, it->v); 
        it = it -> next;
    }
}

void clearEnv()
{

}

