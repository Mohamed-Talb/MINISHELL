#include "../minishell.h"

int	exitestatus(int status)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGQUIT)
            printf("Quit (core dumped)\n");
        return (128 + WTERMSIG(status));
    }
    else
    {
        return (WEXITSTATUS(status));
    }
}
