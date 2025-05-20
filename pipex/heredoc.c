/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:35:51 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/14 13:51:32 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc(t_info *info, char **av)
{
	char	*cmp;
	char	*line;
	int		fd;

	cmp = ft_strjoin(av[2], "\n");
	if (!cmp)
		displayerrors(info, "memory allocation failed\n", 1);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		displayerrors(info, "open file faild\n", 1);
	ft_printf("> ");
	line = ft_getnextline(0);
	while (line && ft_strcmp(line, cmp))
	{
		ft_putstr_fd(line, fd);
		ft_printf("> ");
		free(line);
		line = ft_getnextline(0);
	}
	if (cmp)
		free(cmp);
	free(line);
	close(fd);
}
