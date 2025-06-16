#include "minishell.h"

int completline(t_data *data)
{
	char *completline;
	int i;
	int j;

	i = 0;
	completline = NULL;
	if (data->line[0] != 0 && data->line[0] != '|')
	{
		i = ft_strlen(data->line) - 1;
		while (i >= 0 && ft_iswhitespace(data->line[i]))
			i--;
		j = i - 1;
		if (j == -1)
			return 0;
		while (j >= 0 && ft_iswhitespace(data->line[j]))
			j--;
		if (data->line[j] == '|')
			return 0;
		if (i >= 0 && data->line[i] == '|')
		{
			completline = readline("> ");
			while (completline && completline[0] == '\0')
			{
				free(completline);
				completline = readline("> ");
			}
			if (completline == NULL)
			{
				ft_putstr_fd("syntax error: unexpected end of input\n", 2);
				reset_data(data);
				return 1;
			}
			data->line = ft_strjoin_fc(data->line, completline, 3);
		}
	}
	return 0;
}


void prompter(t_data *data)
{
	char *str;

	str = "\e[1;96m⟦ minishell ⟧\e[0m \e[1;92m>>\e[0m ";
	if (data->last_exit_status != 0)
		str = "\e[1;96m⟦ minishell ⟧\e[0m \e[1;91m>>\e[0m ";
	data->line = readline(str);
	add_history(data->line);
}

void minishell(t_data *data)
{
	struct sigaction sa;
	while(1)
	{
		signals(&sa, 1);
		prompter(data);
		if (data->line == NULL)
			break;
		if (completline(data))
			continue;
		if (parser(data, data->line))
			continue ;
		if (data->command_count == 0)
			continue ;
		grammer(data);
		if (data->command_count == 1 && data->cmds[0]->flags && check_builtin(data->cmds[0]->flags[0]))
			execute_builtin(data, data->cmds[0]);
		else
			parent(data);
		reset_data(data);
	}
}

int main(int ac, char **av, char **penv)
{
	(void) ac;
	(void) av;
	t_data *data;

	data = init_data(penv);
	minishell(data);
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	return (0);
}
