//
// Created by federico ponzi on 15/10/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "inc/myshell.h"

int main(int argc, char* argv[])
{
    printf("Have fun using My Shell! \n");

    init();
    mainLoop();

    return EXIT_SUCCESS;
}