#include "../minishell.h"

int ft_echo(int argc, char **argv, t_data *data)
{
	int rm_newline;
	int i;

	i = 1;
	(void) data;
	rm_newline = 0;
	while (i < argc && !ft_strcmp("-n", argv[i]))
	{
		rm_newline = 1;
		i++;
	}
	while (i < argc - 1)
	{
		ft_putstr(argv[i]);
		ft_putchar(' ');
		i++;
	}
	if (argv[i] != NULL)
		ft_putstr(argv[i]);
	if (rm_newline != 1)
		ft_putchar('\n');
	return (0);
}
