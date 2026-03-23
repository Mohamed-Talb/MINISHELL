/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 09:38:18 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/05 12:05:49 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	upoldpwd(t_data *data)
{
	char	*new;

	new = ft_getenv(data->exported, "PWD");
	if (new == NULL)
	{
		data->exported = envup(data->exported, "OLDPWD");
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

static	int	uppwd(t_data *data)
{
	char	*buff;
	char	*new;

	if (!rgetenv(data->exported, "PWD"))
		return (0);
	buff = getcwd(NULL, 0);
	if (!buff)
	{
		perror("minishell: cd");
		return (1);
	}
	new = ft_strjoin("PWD=", buff);
	ft_free(buff);
	if (!new)
		return (1);
	data->exported = envup(data->exported, new);
	ft_free(new);
	if (!data->exported)
		return (1);
	return (0);
}

static	int	changedir(t_data *data, char *path)
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
			eputf(HOME_ERROR, NULL);
			return (1);
		}
		else if (homepath[0] == 0)
			return (0);
		chdirreturn = chdir(homepath);
		path = homepath;
	}
	if (chdirreturn != 0)
	{
		eputf("minishell: cd: %s: %s\n", (char *[]){path, strerror(errno)});
		return (1);
	}
	return (0);
}

int	ft_cd(int argc, char **argv, t_data *data)
{
	if (argc > 2)
	{
		eputf(ARG_ERROR, (char *[]){"cd"});
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
