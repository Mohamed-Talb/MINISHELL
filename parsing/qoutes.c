#include "../minishell.h"

char *single_q(t_data *data, char *token, char **line)
{
	char *s;

	s = *line + 1;
	while (*s != '\0' && *s != '\'')
	{
		token = ft_append(token, *s, -1);
		s++;
	}
	if (*s == '\'')
		s++;
	else
		errors(data, "minishell: syntax error: unclosed quote\n");
	*line = s;
	return (token);
}


int double_q(t_data *data, t_dlist *token, char **line, int state)
{
	char *s;
	
	s = *line;
	s++;
	while(*s != '"' && *s != 0)
	{
		if(*s == '$' && state == 1)
			token->content = expand(data, token->content, &s);
		else
		{
			token->content = ft_append(token->content, *s, -1);
			s++;
		}
	}
	if (*s == '"')
		s++;
	else
		errors(data, "minishell: syntax error: unclosed quote\n");
	*line = s;
	return (0);
}