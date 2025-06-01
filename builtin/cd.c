#include "../minishell.h"

int ft_cd(int argc, char **argv, t_data *data)
{
	(void) data;
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (argv[1] != NULL)
		chdir(argv[1]);
	else
		chdir(getenv("HOME")); // there is a chance home is not set
	return (0);
}
