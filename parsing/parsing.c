#include "../minishell.h"

int parsing_errors(t_data *data, t_list *list)
{
	if (!list)
	{
		reset_data(data);
		return (1);
	}
	while (list)
	{
		if (list->error)
		{
			ft_putstr_fd(list->error, 2);
			reset_data(data);
			return (1);
		}
		list = list->next;
	}
	return 0;
}

t_list *creat_node(t_data *data)
{
	char *str;
	t_list* new;

	str = ft_strdup("");
	new = ft_lstback(&data->cmd_list, str);
	if (str == NULL || new == NULL)
		errors(data, MALLOC_ERROR, 1);
	return (new);
}

int regular_parse(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	if (*s == '\'')
		single_q(data, token, &s);
	else if (*s == '"')
		double_q(data, token, &s, 1);
	else if (*s == '<' || *s == '>')
	{
		redirection(data, token, &s);
		return (1);
	}
	else if (*s == '|')
	{
		hpipe(data, token, &s);
		data->pipes_nb++;
		return (2);
	}
	else
	{
		token->content = ft_append(token->content, *s, -1);
		s++;
	}
	*line = s;
	return (0);
}

t_list *handle_arg(t_data *data, t_list *token, char **line)
{
	char *s;
	int result;

	s = *line;
	while (*s != '\0' && !ft_iswhitespace(*s))
	{
		if (*s == '$')
			expand(data, &s);
		else
		{
			if (token == NULL)
				token = creat_node(data);
			if (data->expand_rage == 0)
			{
				result = regular_parse(data, token, &s);
				if (result == 1)
					continue;
				if (result == 2)
					break;
			}
			else
			{
				token->content = ft_append(token->content, *s, -1);
				data->expand_rage--;
				s++;
			}
		}
	}
	*line = s;
	return (token);
}

int parser(t_data *data, char *line)
{
	t_list	*new;
	int		new_pipe;

	new_pipe = 1;
	while (*line != '\0')
	{
		if (ft_iswhitespace(*line) == false)
		{
			new = handle_arg(data, NULL, &line);
			if (new != NULL)
			{
				if (new->content != NULL && new->type != PIPE && new_pipe == 1)
				{
					data->command_count++;
					new_pipe = 0;
				}
				else
					new_pipe = 1;
			}
		}
		if (*line == '\0')
			break ;
		line++;
	}
	if (parsing_errors(data, data->cmd_list) == 1)
		return (1);
	return (0);
}
