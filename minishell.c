#include "minishell.h"

void print_cmds(t_data *data)
{
	int i;

	i = 0;
	while (data->cmds[i])
	{
		printf("%s\n", data->cmds[i]->cmd);
		printdoule(data->cmds[i]->flags);
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
		grammer(data);
		parent(data);
		reset_data(data);
	}
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	return (0);
}
