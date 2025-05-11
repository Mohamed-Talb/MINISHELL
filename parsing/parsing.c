#include "../minishell.h"

int handle_arg(t_data *data, t_dlist *token, char **line)
{
	char *s;

	s = *line;
	while (*s != '\0' && !ft_iswhitespace(*s))
	{
		if (*s == '\'')
			token->content = single_q(data, token->content, &s);
		else if (*s == '"')
		{
			double_q(data, token, &s, 1);
		}
		else if(*s == '$')
		{
			token->content = expand(data, token->content, &s);
		}
		else if (*s == '<' || *s == '>')
		{
			redirect(data, token, &s);
			break;
		}
		else if (*s == '|')
		{
			hpipe(data, token, &s);
			break;
		}
		else
		{
			token->content = ft_append(token->content, *s, -1);
			s++;
		}
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
			ft_dlstback(&data->cmd_list, ft_strdup(""));
			handle_arg(data, ft_dlstlast(data->cmd_list), &line);
		}
		if (*line == '\0')
			return (0);
		line++;
	}
	return (0);
}