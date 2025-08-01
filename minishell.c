/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:55:08 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/01 22:36:44 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompter_gnl(t_data *data)
{
	char	*str;

	str = PROMPT_DEFAULT;
	if (isatty(fileno(stdin)))
		data->line = readline(str);
	else
	{
		char *ln;
		ln = get_next_line(fileno(stdin));
		data->line = ft_strtrim(ln, "\n");
		free(ln);
	}
	if (!data->line)
	{
		data->line = NULL;
		return ;
	}
	add_history(data->line);
}

void	prompter(t_data *data)
{
	data->line = readline(PROMPT_DEFAULT);
	if (!data->line)
	{
		data->line = NULL;
		return ;
	}
	add_history(data->line);
}

void	minishell(t_data *data)
{
	while (1)
	{
		signals();
		signal_state(0);
		reset_data(data);
		// prompter_gnl(data);
		prompter(data);
		if (data->line == NULL)
		{
			// printf("exit\n"); // maybe not stderr
			break ;
		}
		if (parser(data, data->line, 0))
			continue ; 
		grammer(data);
		if (openallherdocs(data))
			continue ;
		if (data->pipes_nb == 1 && data->cmds[0]->flags
			&& check_builtin(data->cmds[0]->flags[0]))
			builtin(data, data->cmds[0]);
		else
			parent(data);
	}
}

int	main(int ac, char **av, char **penv)
{
	t_data	*data;

	(void)ac;
	(void)av;
	
	data = init_data(penv);
	*get_data() = data;
	minishell(data);
	rl_clear_history();
	// free_all_adresses();
	exit(data->exit_code);
	return (0);
}
