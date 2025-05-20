/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:17:35 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/14 14:39:23 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_info
{
	char	*cmd;
	char	**flags;
	char	**paths;
	int		inf;
	int		outf;
	int		ac;
	bool	found;
	bool	permission;
}	t_info;

char	**getargs(char *av);
void	check(t_info *info, int i);
void	freeinfo(t_info *info);
void	initinfo(t_info **info);
int		exitestatus(int status);
void	heredoc(t_info *info, char **av);
void	getinfo(t_info *info, char *av, char **env);
void	closefds(int fd1, int fd2, int fd3, int fd4);
int		child(t_info *info, char *av, char **env, int *end);
void	displayerrors(t_info *info, char *error, int exitcode);

#endif