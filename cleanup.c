#include "minishell.h"

void reset_data(t_data *data)
{
	int i;

	if (data->cmds)
	{
		i = 0;
		while (data->cmds[i])
		{
			free(data->cmds[i]->cmd);
			// ft_dlstclear(&data->cmds[i]->allred);
			free(data->cmds[i]);
			i++;
		}
		free(data->cmds);
		data->cmds = NULL;
	}
	if (data->cmd_list != NULL)
	{
		ft_dlstclear(&data->cmd_list);
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
	reset_data(data);
	if (data != NULL)
	{
		free(data);
		data = NULL;
	}
}
