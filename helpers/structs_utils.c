#include "../minishell.h"

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
	data->exported = adjust_shell_level(ft_strdup2(penv), 1);
	other_env(data);
	sync_envs(data);
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
		data->cmds[i]->pipein = -1;
		data->cmds[i]->pipeout = -1;
		data->cmds[i]->infd = -1;
		data->cmds[i]->outfd = -1;
		i++;
	}
	data->cmds[i] = NULL;
	return (0);
}
