/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:38:18 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/24 17:16:42 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	upoldpwd(t_data *data)
{
	char	*new;

	new = ft_getenv(data->exported, "PWD");
	if (new == NULL)
	{
		envup(data->exported, "OLDPWD");
	}
	else
	{
		new = ft_strjoin("OLDPWD=", new);
		data->exported = envup(data->exported, new);
		ft_free(new);
	}
	if (!data->exported)
		return (1);
	return (0);
}

static int	uppwd(t_data *data)
{
	char	*buff;
	char	*new;

	buff = getcwd(NULL, 0);
	if (ft_getenv(data->env, "PDW"))
		return (0);
	if (buff == NULL)
	{
		perror("minshell: cd");
		return (1);
	}
	else
		new = ft_strjoin("PWD=", buff);
	data->exported = envup(data->exported, new);
	free(buff);
	ft_free(new);
	if (!data->exported)
		return (1);
	return (0);
}

static int	changedir(t_data *data, char *path)
{
	int		chdirreturn;
	char	*homepath;

	if (path != NULL)
		chdirreturn = chdir(path);
	else
	{
		homepath = ft_getenv(data->exported, "HOME");
		if (homepath == NULL)
		{
			eputf(HOME_ERROR, 2);
			return (1);
		}
		else if (homepath[0] == 0)
			return (0);
		chdirreturn = chdir(homepath);
	}
	if (chdirreturn != 0)
	{
		if (path == NULL)
			path = homepath;
		eputf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_cd(int argc, char **argv, t_data *data)
{
	if (argc > 2)
	{
		ft_putstr_fd(ARG_ERROR, 2);
		return (1);
	}
	if (changedir(data, argv[1]))
		return (1);
	if (upoldpwd(data))
		return (1);
	if (uppwd(data))
		return (1);
	sync_envs(data);
	return (0);
}
