#include "../minishell.h"

void single_q(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line + 1;
	while (*s != '\0' && *s != '\'')
	{
		token->content = ft_append(token->content, *s, -1);
		s++;
	}
	if (*s == '\'')
		s++;
	else
		set_errors(data, "minishell: syntax error: unclosed quote\n", 1);
	*line = s;
}

void double_q(t_data *data, t_list *token, char **line, int state)
{
	char *s;
	
	s = *line;
	s++;
	while(*s != '"' && *s != 0)
	{
		if(*s == '$' && state == 1 && *(s + 1) != '"')
		{
			expand(data, &s);
		}
		else
		{
			token->content = ft_append(token->content, *s, -1);
			s++;
		}
	}
	
	if (*s == '"')
		s++;
	else
		set_errors(data, "minishell: syntax error: unclosed quote\n", 1);
	data->expand_rage = 0;	
	*line = s;
}
