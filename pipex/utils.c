/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:37:31 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/13 15:47:43 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freeinfo(t_info *info)
{
	if (!info)
		return ;
	if (info->cmd)
		free(info->cmd);
	if (info->paths)
		ft_freedouble(&info->paths);
	if (info->flags)
		ft_freedouble(&info->flags);
	free(info);
	info = NULL;
}

void	initinfo(t_info **info)
{
	if (!*info)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	(*info)->inf = -1;
	(*info)->outf = -1;
	(*info)->cmd = NULL;
	(*info)->flags = NULL;
	(*info)->paths = NULL;
}

void	displayerrors(t_info *info, char *error, int exitcode)
{	
	if (info->inf != -1)
		close(info->inf);
	if (info->outf != -1)
		close(info->outf);
	ft_putstr_fd(error, 2);
	freeinfo(info);
	unlink("here_doc");
	exit(exitcode);
}

void	closefds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != -1)
		close (fd1);
	if (fd2 != -1)
		close (fd2);
	if (fd3 != -1)
		close (fd3);
	if (fd4 != -1)
		close (fd4);
}

int	exitestatus(int status)
{
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}
