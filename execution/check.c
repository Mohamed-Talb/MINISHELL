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
		errcln(data, 127, "%s: command not found\n", command->flags[0]);
	if (!permission)
		errcln(data, 126, "%s: permission denied\n", command->flags[0]);
}

char 	**helper(t_data *data, t_cmds *command)
{
	char **paths = malloc(2 * sizeof(char *));
	if (!paths)
		errors(data, MALLOC_ERROR, 1);
	paths[0] = ft_strdup(command->cmd);
	paths[1] = NULL;
	return paths;
}

static char	**getabspaths(t_data *data, t_cmds *command)
{
	int i;
	char **paths;

	if (ft_strchr(command->cmd, '/'))
	{
		paths = helper(data, command);
		return paths;
	}
	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin_fc(paths[i], "/", 1);
		if (!paths[i])
			errors(data, MALLOC_ERROR, 1);
		paths[i] = ft_strjoin_fc(paths[i], command->cmd, 1);
		if (!paths[i])
			errors(data, MALLOC_ERROR, 1);
		i++;
	}
	return paths;
}

int isDirectory(const char *path) 
{
	struct stat sb;
	return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
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
	if (isDirectory(command->flags[0]))
	{
		eputf("minishell: %s: Is a directory\n", command->flags[0]);
		errors(data, NULL, 126);
	}
	if (command->cmd[0] == 0)
		printerrors(data, command, false, false);
	paths = getabspaths(data, command);
	if (!paths || !paths)
		errors(data, MALLOC_ERROR, 1);
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			found = true;
			if (access(paths[i], X_OK) == 0)
			{
				permission = true;
				if (command->cmd)
					free(command->cmd);
				command->cmd = ft_strdup(paths[i]);
				if (!command->cmd)
					errors(data, MALLOC_ERROR, 1);
				break ;
			}
		}
		i++;
	}
	if (!found || !permission)
		printerrors(data, command, found, permission);
}
