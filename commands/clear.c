#include <stdio.h>
#include <stdlib.h>


int clearCommand(char ** args)
{
    printf("\033[2J"); /*clear screen*/
    printf("\033[1;1H"); /*put at upper left*/

    return 0;
}
