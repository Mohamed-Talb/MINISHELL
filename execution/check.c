/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:06:05 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/18 13:30:57 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerrors(t_data *data, t_cmds *command, int found, int permission)
{
	if (!found)
	{
		if (ft_strchr(command->cmd, '/'))
			eputf(NO_SUCH_F_D, command->flags[0]);
		else
			eputf(CMD_NOT_FOUND, command->flags[0]);
		errors(data, NULL, 127);
	}
	else if (!permission)
	{
		eputf(PERMISSIONS_DENIED, command->flags[0]);
		errors(data, NULL, 126);
	}
}

static char	**getabspaths(t_data *data, t_cmds *command)
{
	int i;
	char **paths;
	char *env_path;

	i = 0;
    if (ft_strchr(command->cmd, '/'))
        return NULL;
    env_path = ft_getenv(data->exported, "PATH");
    if (!env_path || env_path[0] == 0)
    {
        command->cmd = ft_strjoin("./", command->cmd);
        return NULL;
    }
	paths = ft_split(env_path, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin_fc(paths[i], "/", 1);
		paths[i] = ft_strjoin_fc(paths[i], command->cmd, 1);
		i++;
	}
	return (paths);
}

static int cmd_isvalid(char *path, int *found, int *permission)
{
	if (access(path, F_OK) == 0)
	{
		*found = 1;
		if (access(path, X_OK) == 0)
		{
			*permission = 1;
			return 1;
		}
	}
	return 0;
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
	int found;
	char **paths;
	int permission;
	
	i = 0;
	found = false;
	permission = false;
	if (command->cmd[0] == 0)
		printerrors(data, command, false, false);
	paths = getabspaths(data, command);
	if (!paths)
	{
		isDirectory(data, command);
		if (cmd_isvalid(command->cmd, &found, &permission))
			return ;
		else
			printerrors(data, command, found, permission);
	}
	else
	{
		while (paths[i])
		{
			if (cmd_isvalid(command->cmd, &found, &permission))
			{
				command->cmd = ft_strdup(paths[i]);
				return ;
			}
			i++;
		}
		printerrors(data, command, found, permission);
	}	
}
