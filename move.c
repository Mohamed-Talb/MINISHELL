
#include "minishell.h"

int expand()
{
	return (0);
}

int single_q()
{
	return (0);
}

int double_q()
{
	return (0);
}

char	**getargs(t_data *data, char *line)
{
	int i;
	int state;  // 0- string; 1- single quotes; 2- double quotes....
	char	**ptr;

	state = 0;
	i = 0;
	(void) data; (void) ptr; // shuting up the stupid compiler
	while (line[i])
	{
		i++;
	}
	return (NULL);
}

int handle_arg(t_data *data, int *i)
{
	t_dlist *current_arg;

	current_arg = ft_dlstlast(data->cmd_list);
	while (data->line[(*i)] != '\0' && !isspace(data->line[(*i)]))
	{
		current_arg->content = ft_append(current_arg->content, data->line[(*i)], -1);
		(*i)++;
	}
	return (0);
}

int parser(t_data *data)
{
	int i;

	i = 0;
	while (1)
	{
		if (!isspace(data->line[i]))
		{
			ft_dlstback(&data->cmd_list, ft_strdup(""));
			handle_arg(data, &i);
		}
		if (data->line[i] == '\0')
			return (0);
		i++;
	}
}

int main()
{
	t_data data = {0};

	data.line = "echo hello world 'haha nigga'";
	parser(&data);
	ft_dlstiter(data.cmd_list, f);
}