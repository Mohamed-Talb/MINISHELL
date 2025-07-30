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
	int	i;
	int	pid;
	int	status;

	i = 0;
	while (data->cmds[i + 1])
	{
		if (pipe(end) == -1)
		{
			eputf("Pipe creation failed\n");
			errors(NULL, 1);
		}
		ft_memcpy(data->cmds[i]->outpipe, end, 2 * sizeof(int));
		child(data, data->cmds[i]);
		ft_memcpy(data->cmds[i + 1]->inpipe, end, 2 * sizeof(int));
		i++;
	}
	pid = child(data, data->cmds[i]);
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0);
	data->exit_code = exitestatus(status);
	return (data->exit_code);
}
