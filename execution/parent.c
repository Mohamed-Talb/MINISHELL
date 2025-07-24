/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:53:44 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/24 17:37:54 by mtaleb           ###   ########.fr       */
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
		{
			eputf("Pipe creation failed\n");
			errors(NULL, 1);
		}
		data->cmds[i]->outfd = end[1];
		child(data, data->cmds[i]);
		data->cmds[i + 1]->infd = end[0];
		i++;
	}
	pid = child(data, data->cmds[i]);
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	data->exit_code = exitestatus(status);
	return (data->exit_code);
}
