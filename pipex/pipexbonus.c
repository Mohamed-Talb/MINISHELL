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

#include "pipex.h"

static int	bonusparent(t_info *info, char **av, char **env, int i)
{
	int	end[2];
	int	loop;

	int (pid), (status), out = info->ac - 1;
	loop = info->ac - (i + 2);
	while (loop > 0)
	{
		if (pipe(end) == -1)
			displayerrors(info, "Pipe creation failed\n", 1);
		info->outf = end[1];
		child(info, av[i], env, end);
		info->inf = end[0];
		i++;
		loop--;
	}
	if (!ft_strcmp(av[1], "here_doc"))
		info->outf = open(av[out], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		info->outf = open(av[out], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = child(info, av[i], env, end);
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (exitestatus(status));
}

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	int (index), exitcode;
	if (ac < 5)
	{
		ft_putstr_fd("invalide arguments\n", 2);
		exit(1);
	}
	index = 2;
	info = malloc(sizeof(t_info));
	initinfo(&info);
	info->ac = ac;
	if (!ft_strcmp(av[1], "here_doc"))
	{
		heredoc(info, av);
		info->inf = open("here_doc", O_RDONLY);
		index = 3;
	}
	else
		info->inf = open(av[1], O_RDONLY);
	exitcode = bonusparent(info, av, envp, index);
	unlink("here_doc");
	freeinfo(info);
	exit(exitcode);
}
