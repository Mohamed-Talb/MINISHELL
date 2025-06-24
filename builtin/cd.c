#include "../minishell.h"

/*
	1 - sometimes we update in env and sometimes in exported, but we need consistency, both should be updated in all builtin and outside
	2 - should add caching bash doesnt only rely on pwd in env, in case pwd fails like in mkdir example, we use cached version
*/

static int upoldpwd(t_data *data)
{
	char *new;

	new = ft_getenv(data->env, "PWD");
	new = ft_strjoin("OLDPWD=", new);
	data->env = envup(data->env, new);
	free(new);
	if (!data->env)
		return (1);
	return (0);
}

static int uppwd(t_data *data, char *path)
{
	char buff[999999];
	char *new;

	if (!getcwd(buff, 999999))
	{
		eputf("cd: %s: %s\n", GETCWD_ERR, strerror(errno));
		new = ft_getenv(data->env, "PWD");
		new = append(new - 4, '/');
		new = ft_strjoin_fc(new, path, 1);
	}
	else
		new = ft_strjoin("PWD=", buff);
	if (!new)
		return(eputf(MALLOC_ERROR), 1);
	data->env = envup(data->env, new);
	if (!data->env)
		return (1);
	return 0;
}


int changedir(t_data *data, char *path)
{
	int chdirreturn = 0;
	char *error;
	char *homepath;

	if (path != NULL)
		chdirreturn = chdir(path);
	else
	{
		homepath = ft_getenv(data->env,"HOME");
		if (homepath == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		else if (homepath[0] == 0)
			return (0);
		chdirreturn = chdir(homepath);
	}
	if (chdirreturn != 0)
	{
		error = ft_strjoin("minishell: cd: ", path);
		perror(error);
		free(error);
		return (1);
	}
	return (0);
}

char *get_cdpath(t_data *data, char *path)
{
	char **cdpaths;
	char *cdpath;
	int i;

	cdpath = ft_getenv(data->env, "CDPATH");
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
		return 1;
	if (uppwd(data, argv[1]))
		return 1;
	return (0);
}
