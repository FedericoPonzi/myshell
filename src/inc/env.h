#ifndef ENV_H
#define ENV_H


typedef struct env_st{
    char* k;
    char* v;
    struct env_st *next;
}Env;


extern Env **environment;

void addEnv(char* k, char* v);
void addEnvInt(char* k, int v);
void initEnv();
void clearEnv();
void showEnv();

#endif
