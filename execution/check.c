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

static void	printerrors(t_data *data, bool found, bool permission)
{
	if (!found)
		errors(data, "command not found\n", 127);
	if (!permission)
		errors(data, "permission denied\n", 126);
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

void	check(t_data *data, t_cmds *command)
{
	int  i;
	bool found;
	char **paths;
	bool permission;
	
	i = 0;
	found = false;
	permission = false;
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
		printerrors(data, found, permission);
}
