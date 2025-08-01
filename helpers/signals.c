/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:16:26 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/01 22:29:59 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	signal_state(int state)
{
	static int	value;

	if (state != -1)
		value = state;
	return (value);
}

void	hanlder(int sig)
{
	t_data	*data;

	data = *get_data();
	(void)sig;
	if (signal_state(-1) == 0)
	{
		write(1, "\n", 1);
		data->exit_code = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal_state(-1) == 1)
	{
		write(1, "\n", 1);
		free_all_adresses();
		exit(130);
	}
}

void	signals(void)
{
	signal(SIGINT, hanlder);
	signal(SIGQUIT, SIG_IGN);
}
