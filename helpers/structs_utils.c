#include "../minishell.h"

t_data *init_data(char **penv)
{
	t_data *data;
	
	data = calloc(1, sizeof(t_data));
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
	data->cmds = malloc((data->pipes_nb + 1) * sizeof(t_cmds *));
	if (data->cmds == NULL)
	{
		errors(data, MALLOC_ERROR, 1);
		return (1);
	}
	int i = 0;
	while (i < data->pipes_nb)
	{
		data->cmds[i] = malloc(sizeof(t_cmds));
		if (data->cmds[i] == NULL)
		{
			errors(data, MALLOC_ERROR, 1);
			return (1);
		}
		data->cmds[i]->allred = NULL;
		data->cmds[i]->cmd = NULL;
		data->cmds[i]->flags = NULL;
		data->cmds[i]->pipein = -1;
		data->cmds[i]->pipeout = -1;
		i++;
	}
	data->cmds[i] = NULL;
	return 0;
}

void reset_data(t_data *data)
{
	int i;

	if (data == NULL)
		return ;
	if (data->cmds)
	{
		i = 0;
		while (data->cmds[i])
		{
			free(data->cmds[i]->cmd);
			free(data->cmds[i]);
			i++;
		}
		free(data->cmds);
		data->cmds = NULL;
	}
	if (data->cmd_list != NULL)
	{
		ft_lstclear(&data->cmd_list);
		data->cmd_list = NULL;
	}
	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}
	data->pipes_nb = 1;
}

void free_data(t_data *data)
{
	if (data != NULL)
	{
		reset_data(data);
		free(data);
		data = NULL;
	}
}
