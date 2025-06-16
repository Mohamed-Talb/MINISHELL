#include "../minishell.h"

int ft_echo(int argc, char **argv, t_data *data)
{
	int rm_newline;
	int i;
	int j;

	i = 1;
	(void) data;
	rm_newline = 0;
	while (i < argc && !ft_strncmp("-n", argv[i], 2))
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != 'n' && argv[i][j] != 0)
			break;
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
