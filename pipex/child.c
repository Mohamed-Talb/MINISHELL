/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:36:35 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/14 14:22:01 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(t_info *info, char *av, char **env, int *end)
{
	getinfo(info, av, env);
	check(info, 0);
	dup2(info->inf, 0);
	dup2(info->outf, 1);
	closefds(info->inf, info->outf, end[1], end[0]);
	execve(info->cmd, info->flags, env);
	displayerrors(info, "execve failed\n", 126);
}

int	child(t_info *info, char *av, char **env, int *end)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (info->outf == -1)
			displayerrors(info, "invalid outfile\n", 1);
		if (info->inf == -1)
			displayerrors(info, "invalid infile\n", 1);
		exec(info, av, env, end);
	}
	else if (pid > 0)
	{
		close(info->inf);
		close(info->outf);
	}
	else
		displayerrors(info, "Unable to create a new process\n", 1);
	return (pid);
}
