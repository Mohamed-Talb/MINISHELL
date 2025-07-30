/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:35:55 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/19 10:45:28 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_data *data, t_cmds *command, char *cmdname)
{
	int	exst;

	exst = 0;
	if (!ft_strcmp(cmdname, "echo"))
		exst = ft_echo(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "cd"))
		exst = ft_cd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "pwd"))
		exst = ft_pwd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "export"))
		exst = ft_export(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "unset"))
		exst = ft_unset(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "env"))
		exst = ft_env(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "exit"))
	{
		exst = ft_exit(ft_strlen2(command->flags), command->flags, data);
		eputf("exit\n");
		if (exst == -1)
			exst = 1;
		else
			(free_all_adresses(), exit(exst));
	}
	return (exst);
}

void	builtin(t_data *data, t_cmds *command)
{
	int		exst;
	int		stdin_dup;
	char	*cmdname;
	int		stdout_dup;

	stdin_dup = dup(0);
	stdout_dup = dup(1);
	cmdname = command->flags[0];
	if (duplication(data, data->cmds[0]) != -1)
	{
		exst = execute_builtin(data, command, cmdname);
		data->exit_code = exst;
	}
	else
		data->exit_code = 1;
	dup2(stdin_dup, 0);
	dup2(stdout_dup, 1);
}
