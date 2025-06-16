#include "minishell.h"

void completline(t_data *data)
{
	char *completline;
	int i;
	
	i = 0;
	completline = NULL;
	if (data->line)
	{
		while (data->line[i])
			i++;
		if (i > 0)
			i--;
		while (ft_iswhitespace(data->line[i]))
			i--;
		if (data->line[i] == '|')
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
}

void prompter(t_data *data)
{
	char *str;

	str = "\e[1;96m⟦ minishell ⟧\e[0m \e[1;92m>>\e[0m ";
	if (data->last_exit_status != 0)
		str = "\e[1;96m⟦ minishell ⟧\e[0m \e[1;91m>>\e[0m ";
	data->line = readline(str);
	add_history(data->line);
	completline(data);
}

int body(t_data *data)
{
	struct sigaction sa;

	signals(&sa, 1);
	prompter(data);
	if (data->line == NULL)
		return (-1);
	parser(data, data->line);
	if (data->command_count == 0)
		return (0);
	grammer(data);
	if (data->command_count == 1 && data->cmds[0]->flags && check_builtin(data->cmds[0]->flags[0]))
		execute_builtin(data, data->cmds[0]);
	else
		parent(data);
	return (0);
}

int main(int ac, char **av, char **penv)
{
	(void) ac;
	(void) av;
	t_data *data;

	data = init_data(penv);
	while (body(data) != -1)
	{
		reset_data(data);
	}
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	return (0);
}
