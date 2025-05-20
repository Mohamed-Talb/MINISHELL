/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:04:32 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/13 16:02:41 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parent(t_info *info, char **av, char **env)
{
	int	pid;
	int	status;
	int	end[2];

	info->inf = open(av[1], O_RDONLY);
	if (pipe(end) == -1)
		displayerrors(info, "Pipe creation failed\n", 1);
	info->outf = end[1];
	child(info, av[2], env, end);
	info->inf = end[0];
	info->outf = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = child(info, av[3], env, end);
	waitpid(pid, &status, 0);
	wait(NULL);
	return (exitestatus(status));
}

int	main(int ac, char **av, char **envp)
{
	t_info	*info;
	int		exitcode;

	if (ac < 5)
	{
		ft_putstr_fd("invalide arguments\n", 2);
		exit(1);
	}
	info = malloc(sizeof(t_info));
	initinfo(&info);
	exitcode = parent(info, av, envp);
	freeinfo(info);
	exit(exitcode);
}
