#include "minishell.h"

void	prompter(t_data *data)
{
	char	*str;
	char	*line;

	if (data->exit_code == 0)
		str = PROMPT_DEFAULT;
	else
		str = mprintf("%s%d%s", PROMPT_PREFIX, data->exit_code, PROMPT_SUFFIX);
	line = readline(str);
	if (!line)
	{
		data->line = NULL;
		return ;
	}
	data->line = line;
	add_history(data->line);
}

void	minishell(t_data *data)
{
	while (1)
	{
		signals();
		signal_state(0);
		reset_data(data);
		prompter(data);
		if (data->line == NULL)
			break ;
		if (parser(data, data->line))
			continue ; 
		printf("h2\n");
		grammer(data);
		if (openallherdocs(data))
		continue ;
		printf("h3\n");
		if (data->pipes_nb == 1 && data->cmds[0]->flags
		&& check_builtin(data->cmds[0]->flags[0]))
		{
			builtin(data, data->cmds[0]);
		}
		else
		{
			parent(data);
		}
		printf("h4\n");
	}
}

int	main(int ac, char **av, char **penv)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = init_data(penv);
	minishell(data);
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	return (0);
}
