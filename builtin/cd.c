#include "../minishell.h"

static int updating_env(t_data *data, int option)
{
	char *buff = NULL;
	char *newpwdvalue;

	if (option == 1)
	{
		newpwdvalue = getcwd(buff, 999999);
		newpwdvalue = ft_strjoin_fc("PWD=", newpwdvalue, 2);
	}
	else
	{
		newpwdvalue = ft_getenv(data->env, "PWD");
		newpwdvalue = ft_strjoin_fc("OLDPWD=", newpwdvalue, 2);
	}
	upenv(data, newpwdvalue);
	free(newpwdvalue);
	free(buff);
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
			return 0;
		chdirreturn = chdir(homepath);
	}
	if (chdirreturn != 0)
	{
		error = ft_strjoin("minishell: cd: ", path);
		perror(error);
		free(error);
		return 1;
	}
	return 0;
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
	updating_env(data, 0);
	updating_env(data, 1);
	return (0);
}
