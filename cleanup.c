#include "minishell.h"

void free_data(t_data *data)
{
	if (data->line != NULL)
		free(data->line);
	if (data->cmd_list != NULL)
		ft_dlstclear(&data->cmd_list);
	if (data != NULL)
		free(data);
}
