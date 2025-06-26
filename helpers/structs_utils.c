#include "../minishell.h"

void update_lvl(t_data *data)
{
	char *str;
	int pos;
	long value;

	pos = getenvpos(data->env, "SHLVL");
	if (pos == -1)
	{
		data->env = ft_append2(data->env, "SHLVL=1", 0);
	}
	else
	{
		str = ft_getenv(data->env, "SHLVL");
		value = ft_atoy(str);
		if (value > INT_MAX)
			value = 1;
		else
			value++;
		if (value >= 1000)
		{
			eputf("minishell: warning: shell level (1000) too high, resetting to 1\n");
			value = 1;
		}
		data->env[pos] = ft_strjoin_fc("SHLVL=", ft_itoa(value), 2);
	}
}

void other_env(t_data *data)
{
	char buff[99999];
	char *newpwdvalue;

	if (getcwd(buff, 99999) == NULL)
		eputf("shell-init: %s: %s\n", GETCWD_ERR, strerror(errno));
	else
	{
		newpwdvalue = ft_strjoin("PWD=", buff);
		data->exported = envup(data->exported, newpwdvalue);
		free(newpwdvalue);
	}
	data->exported = envup(data->exported, "OLDPWD");
}

t_data	*init_data(char **penv)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (NULL);
	}
	data->env = ft_strdup2(penv);
	update_lvl(data);
	data->exported = ft_strdup2(data->env);
	other_env(data);
	data->pipes_nb = 1;
	return (data);
}

int init_cmds(t_data *data)
{
	int i;

	data->cmds = ft_calloc((data->pipes_nb + 1), sizeof(t_cmds *));
	if (data->cmds == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (1);
	}
	i = 0;
	while (i < data->pipes_nb)
	{
		data->cmds[i] = ft_calloc(1, sizeof(t_cmds));
		if (data->cmds[i] == NULL)
		{
			errors(data, MALLOC_ERROR, 1);
			return (1);
		}
		data->cmds[i]->pipein = -1;
		data->cmds[i]->pipeout = -1;
		i++;
	}
	data->cmds[i] = NULL;
	return (0);
}
