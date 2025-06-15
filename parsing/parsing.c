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

int handle_arg(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	while (*s != '\0' && !ft_iswhitespace(*s))
	{
		if (*s == '\'')
			token->content = single_q(data, token->content, &s);
		else if (*s == '"')
			double_q(data, token, &s, 1);
		else if(*s == '$')
			token->content = expand(data, token->content, &s);
		else if (*s == '<' || *s == '>')
		{
			redirection(data, token, &s);
			break;
		}
		else if (*s == '|')
		{
			hpipe(data, token, &s);
			data->pipes_nb++;
			break;
		}
		else
			token->content = ft_append(token->content, *s, -1);
		s++;
	}
	*line = s;
	return (0);
}

int parser(t_data *data, char *line)
{
	while (*line != '\0')
	{
		if (!ft_iswhitespace(*line))
		{
			ft_lstback(&data->cmd_list, ft_strdup(""));
			handle_arg(data, ft_lstlast(data->cmd_list), &line);
			ft_lstlast(data->cmd_list);
		}
		if (*line == '\0')
			break ;
		line++;
	}
	if (parsing_errors(data, data->cmd_list) == 1)
		return (1);
	return (0);
}
