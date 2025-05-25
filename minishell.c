#include "minishell.h"

void print_cmds(t_data *data)
{
	int i;

	i = 0;
	while (data->cmds[i])
	{
		printdoule(data->cmds[i]->cmd);
		i++;
	}
	printf("\n");
}

int main(int ac, char **av, char **penv)
{
	(void) ac;
	(void) av;
	t_data *data = malloc(sizeof(t_data));
	init_data(data, penv);
	while (1)
	{
		data->line = readline("\e[91m\e[1mminishell:\e[92m~$ \e[0m");
		if (data->line == NULL || !ft_strncmp("exit", data->line, 4))
			break;
		add_history(data->line);
		parser(data, data->line);
		// ft_dlstiter(data->cmd_list, f);
		grammer(data);
		print_cmds(data);
		parent(data);
		printf("here\n");
		// int i = 0;
		// while (i < data->pipes_nb)
		// {
		// 	printf("cmd %d\n", i);
		// 	printdoule(data->cmds[i]->cmd);
		// 	printf("\n");
		// 	ft_dlstiter(data->cmds[i]->allred, f);
		// 	i++;
		// }
		reset_data(data);
	}
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	return (0);
}
