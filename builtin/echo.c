#include "../minishell.h"

void ft_echo(char *str, char *flag)
{	
	if (!ft_strcmp(flag, "-n"))
		ft_putendl_fd(str, 1);
	else
		ft_putstr(str);
}