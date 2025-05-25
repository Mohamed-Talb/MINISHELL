#include <stdio.h>

void main(int ac, char **av)
{
    int i;

    i = 0;
    while (av[i])
    {
        printf("arg: %s\n", av[i]);
        i++;
    }
}