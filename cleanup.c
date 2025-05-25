#include "minishell.h"

void free_data(t_data *data)
{
	int i = 0;
	while (data->cmds[i])
	{
		ft_dlstclear(&data->cmds[i]->allred);
		ft_freedouble(&data->cmds[i]->cmd);
		i++;
	}
	i = 0;
	while (data->cmds[i])
	{
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);
	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->cmd_list != NULL)
		ft_dlstclear(&data->cmd_list);
	if (data != NULL)
		free(data);
}
