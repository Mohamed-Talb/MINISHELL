#include "minishell.h"

void free_data(t_data *data)
{
	ft_dlstclear(&data->cmd_list);
	if (data)
		free(data);
}

