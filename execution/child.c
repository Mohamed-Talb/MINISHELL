/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:04:28 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 09:04:29 by mtaleb           ###   ########.fr       */
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

int	child(t_data *data, t_cmds *command)
{
	int	pid;

	signal_state(2);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		duplication(data, command);
		childexec(data, command);
	}
	else if (pid > 0)
	{
		signal_state(0);
		close(command->infd);
		close(command->outfd);
	}
	else
	{
		eputf("minishell: fork: %s\n", strerror(errno));
		errors(NULL, EXIT_FAILURE);
	}
	return (pid);
}
