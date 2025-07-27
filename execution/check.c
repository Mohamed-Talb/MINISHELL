/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:06:05 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/26 18:05:05 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerrors(t_cmds *cmd)
{
	if (!cmd->found)
	{
		eputf(CMD_NOT_FOUND, cmd->flags[0]);
		errors(NULL, 127);
	}
	else if (!cmd->permission)
	{
		eputf(PERMISSIONS_DENIED, cmd->flags[0]);
		errors(NULL, 126);
	}
}

static int abspath(t_cmds *command)
{
    if (strchr(command->cmd, '/'))
    {
        if (isDirectory(command->cmd))
        {
            eputf(IS_DIR, command->flags[0]);
            errors(NULL, 126);
        }
        else if (command->cmd[strlen(command->cmd) - 1] == '/')
        {
            eputf(IS_NOT_DIR, command->flags[0]);
            errors(NULL, 126);
        }
        return (1);
    }
    return (0);
}

static int cmd_isvalid(t_cmds *command, char *path)
{
	if (isDirectory(path) == false && access(path, F_OK) == 0)
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

static char **getpaths(t_data *data, char *cmd)
{
    char *env_path;
    char **paths;
    int i;

    env_path = ft_getenv(data->exported, "PATH");
    if (!env_path || env_path[0] == 0)
        return NULL;
    paths = ft_split(env_path, ':');
    i = 0;
    while (paths[i])
    {
        char *tmp = mprintf("%s/%s", paths[i], cmd);
        ft_free(paths[i]);
        paths[i] = tmp;
        i++;
    }
    return (paths);
}

void check(t_data *data, t_cmds *command)
{
    char **paths;
    int i;

	if (abspath(command))
		return ;
    paths = getpaths(data, command->cmd);
    if (!paths)
        return;
    i = 0;
    while (paths[i])
    {
        if (cmd_isvalid(command, paths[i]))
        {
            ft_free(command->cmd);
            command->cmd = ft_strdup(paths[i]);
            ft_freedouble(paths);
            return;
        }
        i++;
    }
    ft_freedouble(paths);
    printerrors(command);
}
