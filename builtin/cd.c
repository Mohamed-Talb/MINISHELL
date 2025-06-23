#include "../minishell.h"

/*
	1 - sometimes we update in env and sometimes in exported, but we need consistency, both should be updated in all builtin and outside
	2 - should add caching bash doesnt only rely on pwd in env, in case pwd fails like in mkdir example, we use cached version
*/

static int updating_env(t_data *data, char *path)
{
	char buff[GETCWD_BUFF_SIZE];
	char *newpwdvalue;

	newpwdvalue = getownenv(data->env, "PWD");
	newpwdvalue = ft_strjoin("OLDPWD=", newpwdvalue);
	(ftup_env(data, &data->env, newpwdvalue), free(newpwdvalue));
	if (getcwd(buff, GETCWD_BUFF_SIZE) == NULL)
	{
		eputf("cd: %s: %s\n", GETCWD_ERR, strerror(errno));
		newpwdvalue = getownenv(data->env, "PWD");
		newpwdvalue = append(newpwdvalue - 4, '/');
		newpwdvalue = ft_strjoin_fc(newpwdvalue, path, 1);
	}
	else
		newpwdvalue = ft_strjoin("PWD=", buff);
	(ftup_env(data, &data->env, newpwdvalue), free(newpwdvalue));
	return (0);
}

int changedir(t_data *data, char *path)
{
	int chdirreturn = 0;
	char *error;
	char *homepath;

	if (path != NULL)
	{
		chdirreturn = chdir(path);
	}
	else
	{
		homepath = getownenv(data->env,"HOME");
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

	cdpath = getownenv(data->env, "CDPATH");
	if (cdpath == NULL)
		return (path);
	cdpaths = ft_split(cdpath, ':');
	i = 0;
	while (cdpaths[i])
	{
		i++;
	}
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
	updating_env(data, argv[1]);
	return (0);
}
