/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:04:28 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/31 10:58:38 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(t_data *data, t_cmds *command)
{
	int	exst;

	exst = 0;
	if (!ft_strcmp(command->flags[0], "echo"))
		exst = ft_echo(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "cd"))
		exst = ft_cd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "pwd"))
		exst = ft_pwd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "export"))
		exst = ft_export(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "unset"))
		exst = ft_unset(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "env"))
		exst = ft_env(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "exit"))
	{
		exst = ft_exit(ft_strlen2(command->flags), command->flags, data);
		if (exst == -1)
			exst = 1;
	}
	exit(exst);
}

void	childexec(t_data *data, t_cmds *command)
{
	if (command->flags)
	{
		if (check_builtin(command->flags[0]))
			run_builtin(data, command);
		else
		{
			check(data, command);
			execve(command->cmd, command->flags, data->env);
			eputf("minishell: %s: %s\n", command->flags[0], strerror(errno));
			if (errno == ENOENT)
				errors(NULL, 127);
			else
				errors(NULL, 126);
		}
	}
	else
		errors(NULL, 0);
}

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

void print_open_fds(void) {
    DIR *dir = opendir("/proc/self/fd");
    if (!dir) {
        fprintf(stderr, "opendir failed: %s\n", strerror(errno));
        return;
    }

    struct dirent *entry;
    char path[PATH_MAX];
    char target[PATH_MAX];
    ssize_t len;

    fprintf(stderr, "==== Open file descriptors (pid: %d) ====\n", getpid());
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;

        snprintf(path, sizeof(path), "/proc/self/fd/%s", entry->d_name);
        len = readlink(path, target, sizeof(target) - 1);
        if (len != -1) {
            target[len] = '\0';
            fprintf(stderr, "FD %s → %s\n", entry->d_name, target);
        } else {
            fprintf(stderr, "FD %s → (unreadable: %s)\n", entry->d_name, strerror(errno));
        }
    }
    fprintf(stderr, "=========================================\n");

    closedir(dir);
}


int	child(t_data *data, t_cmds *cmd)
{
	int	pid;

	signal_state(2);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (duplication(data, cmd) == -1)
			errors(NULL, 1);
		// if (ft_strcmp("ls", cmd->cmd) == 0)
		// {
		// 	print_open_fds();
		// }
		childexec(data, cmd);
	}
	else if (pid > 0)
	{
		signal_state(0);
		(ft_close(cmd->inpipe[0]), ft_close(cmd->outpipe[1]));
	}
	else
	{
		eputf("minishell: fork: %s\n", strerror(errno)); // shouldnt we restore signal state to 0 here too? it might be usefull for this error msg before exit??
		(ft_close(cmd->inpipe[0]), ft_close(cmd->outpipe[1]));
		errors(NULL, EXIT_FAILURE);
	}
	return (pid);
}
