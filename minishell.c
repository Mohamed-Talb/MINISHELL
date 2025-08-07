/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:55:08 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/05 12:05:32 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompter(t_data *data)
{
	char	*str;

	str = mprintf("%s[ minishell ]%s %s>>%s ",
			(char *[]){CYAN, RESET, GREEN, RESET});
	data->line = readline(str);
	ft_free(str);
	if (!data->line)
		return ;
	add_history(data->line);
}

int	minishell(t_data *data)
{
	while (1)
	{
		signal_state(0);
		signals();
		reset_data(data);
		prompter(data);
		if (data->line == NULL)
		{
			ft_putstr_fd("exit\n", 2);
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
	return (data->exit_code);
}

int	main(int ac, char **av, char **penv)
{
	t_data	*data;
	int		extc;

	(void)ac;
	(void)av;
	data = init_data(penv);
	*get_data() = data;
	extc = minishell(data);
	rl_clear_history();
	free_all_adresses();
	exit(extc);
}
