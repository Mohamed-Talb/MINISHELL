#include "minishell.h"

void errors(t_data *data, char *error)
{
	ft_putstr_fd(error, 1);
	free_data(data);
	exit(1);
}

int init_data(t_data *data)
{
	if (data == NULL)
	{
		errors(data, MALLOC_ERROR);
		return (1);
	}
	data->cmd_list = NULL;
	data->line = NULL;
	return 0;
}

char	*ft_strjoin_fc(char *str, char *buff, int choice)
{
	char	*new;

	if (!str || !buff)
		return (NULL);
	new = ft_strjoin(str, buff);
	if (choice == 1 || choice == 3)
		free(str);
	if (choice == 2 || choice == 3)
		free(buff);
	return (new);
}

