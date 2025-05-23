#include "minishell.h"

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
		free(data->line);
		duplication(data, data->cmds[0]);
		printf("\n\n\n");
		int i = 0;
		while (i < data->pipes_nb)
		{
			printf("cmd %d\n", i);
			printdoule(data->cmds[i]->cmd);
			printf("\n");
			ft_dlstiter(data->cmds[i]->allred, f);
			i++;
		}
	}
	ft_dlstclear(&data->cmd_list);
	free_data(data);
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	return (0);
}
