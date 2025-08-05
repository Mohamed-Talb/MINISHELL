/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:03:24 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/05 12:05:49 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerrors(t_cmds *cmd)
{
	if (!cmd->found)
	{
		eputf(CMD_NOT_FOUND, (char *[]){cmd->flags[0]});
		errors(NULL, 127);
	}
	else if (!cmd->permission)
	{
		eputf(PERMISSIONS_DENIED, (char *[]){cmd->flags[0]});
		errors(NULL, 126);
	}
}

static int	abspath(t_cmds *command)
{
	if (strchr(command->cmd, '/'))
	{
		if (isdirectory(command->cmd))
		{
			eputf(IS_DIR, (char *[]){command->flags[0]});
			errors(NULL, 126);
		}
		return (1);
	}
	return (0);
}

static int	cmd_isvalid(t_cmds *command, char *path)
{
	if (!isdirectory(path) && access(path, F_OK) == 0)
	{
		command->found = 1;
		if (access(path, X_OK) == 0)
		{
			command->permission = 1;
			return (1);
		}
	}
	return (0);
}

static char	**getpaths(t_data *data, char *cmd)
{
	char	*env_path;
	char	**paths;
	int		i;
	char	*tmp;

	env_path = ft_getenv(data->exported, "PATH");
	if (!env_path || env_path[0] == 0)
		return (NULL);
	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = mprintf("%s/%s", (char *[]){paths[i], cmd});
		ft_free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

void	check(t_data *data, t_cmds *command)
{
	char	**paths;
	int		i;

	if (abspath(command))
		return ;
	paths = getpaths(data, command->cmd);
	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		if (cmd_isvalid(command, paths[i]))
		{
			ft_free(command->cmd);
			command->cmd = ft_strdup(paths[i]);
			ft_freedouble(paths);
			return ;
		}
		i++;
	}
	ft_freedouble(paths);
	printerrors(command);
}
