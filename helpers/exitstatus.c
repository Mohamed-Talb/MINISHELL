#include "../minishell.h"

int	exitestatus(int status)
{
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}
