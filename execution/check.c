/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:06:05 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/24 17:22:45 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerrors(t_cmds *cmd, int found, int perm)
{
	if (!found)
	{
		eputf(CMD_NOT_FOUND, cmd->flags[0]);
		errors(NULL, 127);
	}
	else if (!perm)
	{
		eputf(PERMISSIONS_DENIED, cmd->flags[0]);
		errors(NULL, 126);
	}
}

int isDirectory(t_cmds *command) 
{
	struct stat sb;
	if (ft_strchr(command->cmd, '/'))
	{
		if (stat(command->flags[0], &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			eputf(IS_DIR, command->flags[0]);
			errors(NULL, 126);
		}
		else if (command->cmd[ft_strlen(command->cmd) - 1] == '/')
		{
			eputf(IS_NOT_DIR, command->flags[0]);
			errors(NULL, 126);
		}
		return (1);
	}
	return (0);
}

static int cmd_isvalid(char *path, int *found, int *permission)
{
	if (access(path, F_OK) == 0)
	{
		*found = 1;
		if (access(path, X_OK) == 0)
		{
			*permission = 1;
			return (1);
		}
	}
	return (0);
}

// static char	**getabspaths(t_data *data, t_cmds *command)
// {
// 	int i;
// 	char **paths;
// 	char *env_path;

// 	i = 0;
//     if (ft_strchr(command->cmd, '/'))
//         return NULL;
//     env_path = ft_getenv(data->exported, "PATH");
//     if (!env_path || env_path[0] == 0)
//     {
//         command->cmd = ft_strjoin("./", command->cmd);
//         return NULL;
//     }
// 	paths = ft_split(env_path, ':');
// 	while (paths[i])
// 	{
// 		paths[i] = ft_strjoin_fc(paths[i], "/", 1);
// 		paths[i] = ft_strjoin_fc(paths[i], command->cmd, 1);
// 		i++;
// 	}
// 	return (paths);
// }

void find_cmd(t_data *data, t_cmds *command)
{
	int  i;
	int found;
	char **paths;
	int permission;
	char *env_path;

	i = 0;
	found = false;
	permission = false;

	env_path = ft_getenv(data->exported, "PATH");
	if (!env_path || env_path[0] == 0)
        return ;
	paths = ft_split(env_path, ':');
	while (paths[i])
	{
		paths[i] = mprintf("%f/%s", paths[i], command->cmd);
		if (cmd_isvalid(paths[i], &found, &permission))
		{
			command->cmd = ft_strdup(paths[i]);
			ft_freedouble(paths);
			return ;
		}
		i++;
	}
	(ft_freedouble(paths), printerrors(command, found, permission));
}

void	check(t_data *data, t_cmds *command)
{
	if (command->cmd[0] == '\0' || isDirectory(command))
		return ;
	find_cmd(data, command);
}









// char **getpaths(t_data *data, char *cmd)
// {
//     char *env_path;
//     char **paths;
//     int i;

//     env_path = ft_getenv(data->exported, "PATH");
//     if (!env_path || env_path[0] == 0)
//         return NULL;
//     paths = ft_split(env_path, ':');
//     i = 0;
//     while (paths[i])
//     {
//         char *tmp = mprintf("%s/%s", paths[i], cmd);
//         ft_free(paths[i]);
//         paths[i] = tmp;
//         i++;
//     }
//     return paths;
// }

// void find_cmd(t_data *data, t_cmds *command)
// {
//     char **paths;
//     int i;
//     int found = false;
//     int permission = false;

//     paths = getpaths(data, command->cmd);
//     if (!paths)
//         return;
//     i = 0;
//     while (paths[i])
//     {
//         if (cmd_isvalid(paths[i], &found, &permission))
//         {
//             free(command->cmd);
//             command->cmd = ft_strdup(paths[i]);
//             ft_freedouble(paths);
//             return;
//         }
//         i++;
//     }
//     ft_freedouble(paths);
//     printerrors(command, found, permission);
// }
