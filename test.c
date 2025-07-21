#include "minishell.h"

int main()
{
    int fd = open("", O_RDWR | O_CREAT | O_TRUNC);
    if (fd == -1)
        perror("minishell");
}