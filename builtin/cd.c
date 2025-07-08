#include "../minishell.h"

int upoldpwd(t_data *data)
{
	char *new;

	new = ft_getenv(data->exported, "PWD");
	if (new == NULL)
		data->exported = envup(data->exported, "OLDPWD");
	else
	{
		new = ft_strjoin("OLDPWD=", new);
		data->exported = envup(data->exported, new);
		free(new);
	}
	if (!data->exported)
		return (1);
	return (0);
}

int uppwd(t_data *data, char *path)
{
	char buff[999999];
	char *new;

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		eputf("cd: %s: %s\n", GETCWD_ERR, strerror(errno));
		new = ft_getenv(data->exported, "PWD");
		new = append(new - 4, '/');
		new = ft_strjoin_fc(new, path, 1);
	}
	else
		new = ft_strjoin("PWD=", buff);
	data->exported = envup(data->exported, new);
	if (!data->exported)
		return (1);
	return (0);
}

int changedir(t_data *data, char *path)
{
	int chdirreturn;
	char *homepath;

	if (path != NULL)
		chdirreturn = chdir(path);
	else
	{
		homepath = ft_getenv(data->exported,"HOME");
		if (homepath == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		else if (homepath[0] == 0) // env
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

char *get_cdpath(t_data *data, char *path)
{
	char **cdpaths;
	char *cdpath;
	int i;

	cdpath = ft_getenv(data->exported, "CDPATH");
	if (cdpath == NULL)
		return (path);
	cdpaths = ft_split(cdpath, ':');
	if (!cdpath)
		return(eputf(MALLOC_ERROR), NULL);
	i = 0;
	while (cdpaths[i])
		i++;
	return (path);
}

int ft_cd(int argc, char **argv, t_data *data)
{
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (changedir(data, argv[1]))
		return (1);
	if (upoldpwd(data))
		return (1);
	if (uppwd(data, argv[1]))
		return (1);
	sync_envs(data);
	return (0);
}
