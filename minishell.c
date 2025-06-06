#include "minishell.h"

void completline(t_data *data)
{
	int i = 0;
	char *completline = NULL;
	
	while(data->line[i])
		i++;
	if (data->line[i - 1] == '|')
	{
		completline = readline("> ");
		while (completline[0] == 0 || completline == NULL)
		{
			free(completline);
			completline = readline("> ");
		}
		data->line = ft_strjoin_fc(data->line, completline, 3);
	}
}

int main(int ac, char **av, char **penv)
{
	(void) ac;
	(void) av;
	struct sigaction sa;
	t_data *data = malloc(sizeof(t_data));

	init_data(data, penv);
	while (1)
	{
		signals(&sa, 1);
		data->line = readline("\e[91m\e[1mminishell:\e[92m~$ \e[0m");
		completline(data);
		parser(data, data->line);
		grammer(data);
		if (data->pipes_nb == 1 && data->cmds[0]->flags && check_builtin(data->cmds[0]->flags[0]))
			execute_builtin(data, data->cmds[0]);
		else
			parent(data);
		add_history(data->line);
		reset_data(data);
	}
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	return (0);
}
