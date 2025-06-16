#include "../minishell.h"

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
			// ft_lstclear(&data->cmds[i]->allred);
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
	data->command_count = 0;
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
