#include "../minishell.h"

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
	data->exported = ft_strdup2(penv);
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
