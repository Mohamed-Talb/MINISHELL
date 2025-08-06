/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:03:31 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/06 21:59:37 by mtaleb           ###   ########.fr       */
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
		exst = ft_exit(ft_strlen2(command->flags), command->flags, data);
	free_all_adresses();
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
			eputf("minishell: %s: %s\n",
				(char *[]){command->flags[0], strerror(errno)});
			if (errno == ENOENT)
				errors(NULL, 127);
			else
				errors(NULL, 126);
		}
	}
	else
		errors(NULL, 0);
}

int	child(t_data *data, t_cmds *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal_state(2);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		duplication(data, cmd);
		if (cmd->error)
			errors(cmd->error, 1);
		childexec(data, cmd);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		(ft_close(cmd->inpipe[0]), ft_close(cmd->outpipe[1]));
	}
	else
	{
		eputf("minishell: fork: %s\n", (char *[]){strerror(errno)});
		(ft_close(cmd->inpipe[0]), ft_close(cmd->outpipe[1]));
		errors(NULL, EXIT_FAILURE);
	}
	return (pid);
}
