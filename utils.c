#include "minishell.h"

void errors(t_data *data, char *error)
{
	ft_putstr_fd(error, 1);
	free_data(data);
}

int init_data(t_data *data)
{
	if (!data)
		return (errors(data, MALLOC_ERROR), 1);
	data->cmd_list = NULL;
	data->anything = -1;
	return 0;
}