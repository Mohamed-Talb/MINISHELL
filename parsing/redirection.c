#include "minishell.h"

void redirect_helper(t_data *data, t_dlist *token, char **line)
{
	char *s;

	s = *line;
	while(*s == ' ')
		s++;
	if (*s != '|')
	{
		while (*s != 0 && !ft_iswhitespace(*s))
		{
			if(*s == '"')
			{
				if (token->type == RIGHT_RED || token->type == LEFT_RED)
					double_q(data, token, &s, 1);
				else
					double_q(data, token, &s, 0);
			}
			else if(*s == '\'')
				token-> content = single_q(data, token->content, &s);
			else
			{
				token->content = ft_append(token->content, *s, -1);
				s++;
			}
		}
	}
	else
		printf("error\n");
	*line = s;
}

void redirect(t_data *data, t_dlist *token, char **line)
{
	char *s;


	s = *line;
	if (*s == '>')
	{
		token->type = RIGHT_RED;
		s++;
		if (*s == '>')
		{
			token->type = RIGHT_HER;
			s++;
		}
	}
	else if (*s == '<')
	{
		token->type = LEFT_RED;
		s++;
		if (*s == '<')
		{
			token->type = RIGHT_HER;
			s++;
		}
	}
	if (*s != '|')
	{
		redirect_helper(data, token, &s);
	}
	*line = s;
}