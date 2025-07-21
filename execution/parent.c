/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:53:44 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/19 16:29:36 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parent(t_data *data)
{
	int	end[2];
	int	i = 0;
	int pid;
	int status;

	while (data->cmds[i + 1])
	{
		if (pipe(end) == -1)
			errors(data, "Pipe creation failed\n", 1);
		data->cmds[i]->outfd = end[1];
		child(data, data->cmds[i]);
		data->cmds[i + 1]->infd = end[0];
		i++;
	}
	pid = child(data, data->cmds[i]);
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	data->last_exit_status = exitestatus(status);
	return (data->last_exit_status);
}
