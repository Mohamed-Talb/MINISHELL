/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:55:08 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/29 14:18:40 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompter(t_data *data)
{
	char	*str;
	char	*line;

	if (data->exit_code == 0)
		str = PROMPT_DEFAULT;
	else
		str = mprintf(PROMPT_ERR, data->exit_code);
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
		{
			// ft_putstr_fd("exit", 2);
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
	minishell(data);
	rl_clear_history();
	return (0);
}


// int	main(int ac, char **av, char **penv)
// {
// 	t_data	*data;

// 	((void)ac, (void)av);
// 	data = init_data(penv);
// 	while (true)
// 	{
// 		(signals(), signal_state(0));
// 		reset_data(data);
// 		prompter(data);
// 		if (data->line == NULL)
// 			break ;
// 		if (parser(data, data->line, 0))
// 			continue ;
// 		grammer(data);
// 		if (openallherdocs(data))
// 			continue ;
// 		if (data->pipes_nb == 1 && data->cmds[0]->flags
// 			&& check_builtin(data->cmds[0]->flags[0]))
// 			builtin(data, data->cmds[0]);
// 		else
// 			parent(data);
// 	}
// 	eputf("exit\n");
// 	rl_clear_history();
// 	return (0);
// }
