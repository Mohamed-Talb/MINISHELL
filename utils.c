#include "minishell.h"

void errors(t_data *data, char *error)
{
	ft_putstr_fd(error, 1);
	free_data(data);
}

t_data *init_data()
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		errors(data, MALLOC_ERROR);
		return (NULL);
	}
	data->anything = 5;
	data->cmd_list = NULL;
	return (data);
}
