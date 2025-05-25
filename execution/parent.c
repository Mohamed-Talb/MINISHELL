/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexbonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:53:44 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/14 14:38:06 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exitestatus(int status)
{
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

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
        data->cmds[i]->pipeout = end[1];
		child(data, data->cmds[i]);
		data->cmds[i + 1]->pipein = end[0];
		i++;
	}
	pid = child(data, data->cmds[i]);
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (exitestatus(status));
}