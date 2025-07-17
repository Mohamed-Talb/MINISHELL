#include "../minishell.h"

int	exitestatus(int status)
{
 if (WIFSIGNALED (status))
    return (128 + WTERMSIG (status));
  else
    return (WEXITSTATUS (status));
}