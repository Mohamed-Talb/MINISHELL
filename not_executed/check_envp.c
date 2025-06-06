#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    for (; *envp; envp++)
    {
        printf("%s\n", *envp);
    }
}