#include "minishell.h"

int init_data(t_data *data, char **penv)
{
	if (data == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (1);
	}
	data->cmd_list = NULL;
	data->line = NULL;
	data->env = ft_strdup2(penv);
	data->pipes_nb = 1;
	data->cmds = NULL;
	return 0;
}

int init_cmds(t_data *data)
{
	data->cmds = malloc((data->pipes_nb + 1) * sizeof(t_cmds *));
	if (data->cmds == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (1);
	}
	int i = 0;
	while (i < data->pipes_nb)
	{
		data->cmds[i] = malloc (sizeof(t_cmds));
		if (data->cmds[i] == NULL)
		{
			errors(data, MALLOC_ERROR, 1);
			return (1);
		}
		data->cmds[i]->allred = NULL;
		data->cmds[i]->cmd = NULL;
		data->cmds[i]->pipein = -1;
		data->cmds[i]->pipeout = -1;
		i++;
	}
	data->cmds[i] = NULL;
	return 0;
}