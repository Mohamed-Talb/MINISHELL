#include "minishell.h"

int init_data(t_data *data, char **penv)
{
	if (data == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (1);
	}
	data->env = ft_strdup2(penv);
	data->exported = ft_strdup2(penv);
	data->pipes_nb = 1;
	return 0;
}

int init_cmds(t_data *data)
{
	data->cmds = ft_calloc((data->pipes_nb + 1), sizeof(t_cmds *));
	if (data->cmds == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (1);
	}
	int i = 0;
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
	return 0;
}