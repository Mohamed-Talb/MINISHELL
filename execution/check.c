/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:06:05 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/14 14:24:50 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerrors(t_data *data, t_cmds *command, bool found, bool permission)
{
	if (!found)
	{
		eputf(CMD_NOT_FOUND, command->flags[0]);
		errors(data, NULL, 127);
	}
	else if (!permission)
	{
		eputf(PERMISSIONS_DENIED, command->flags[0]);
		errors(data, NULL, 126);
	}
}

char 	**helper(t_data *data, t_cmds *command)
{
	(void)data;
	char **paths = ft_malloc(2 * sizeof(char *));
	paths[0] = ft_strdup(command->cmd);
	paths[1] = NULL;
	return paths;
}

static char	**getabspaths(t_data *data, t_cmds *command)
{
	int i;
	char **paths;
	char *env_path;
	if (ft_strchr(command->cmd, '/'))
	{
		paths = helper(data, command);
		return (paths);
	}
	i = 0;
	env_path = ft_getenv(data->exported, "PATH");
	if (env_path == NULL)
		return (NULL);
	paths = ft_split(env_path, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin_fc(paths[i], "/", 1);
		paths[i] = ft_strjoin_fc(paths[i], command->cmd, 1);
		i++;
	}
	return (paths);
}

void isDirectory(t_data *data, t_cmds *command) 
{
	struct stat sb;
	if (stat(command->flags[0], &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		eputf("minishell: %s: Is a directory\n", command->flags[0]);
		errors(data, NULL, 126);
	}
}

void	check(t_data *data, t_cmds *command)
{
	int  i;
	bool found;
	char **paths;
	bool permission;
	
	i = 0;
	found = false;
	permission = false;
	isDirectory(data, command);
	if (command->cmd[0] == 0)
		printerrors(data, command, false, false);
	paths = getabspaths(data, command);
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			found = true;
			if (access(paths[i], X_OK) == 0)
			{
				permission = true;
				command->cmd = ft_strdup(paths[i]);
				break ;
			}
		}
		i++;
	}
	if (!found || !permission)
		printerrors(data, command, found, permission);
}
