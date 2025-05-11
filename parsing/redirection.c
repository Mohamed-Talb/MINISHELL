#include "../minishell.h"

void ft_putnstr_fd(char *str, int n, int fd)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void redirect_helper(t_data *data, t_dlist *token, char **line)
{
	char *s;

	while (ft_iswhitespace(**line))
		(*line)++;
	s = *line;
	if (*s == '\0' || in_set("|><", *s) > -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (*s == '\0')
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(*s, 2);
		errors(data, "'\n");
	}
	while (!(*s == '\0' || in_set("|><", *s) > -1 || ft_iswhitespace(*s)))
	{
		if(*s == '"')
		{
			if (token->type == RIGHT_RED || token->type == LEFT_RED || token->type == RIGHT_HER)
				double_q(data, token, &s, 1);
			else
				double_q(data, token, &s, 0);
		}
		if (*s == '$' && token->type != LEFT_HER)
			token->content = expand(data, token->content, &s);
		else if(*s == '\'')
			token->content = single_q(data, token->content, &s);
		else
		{
			token->content = ft_append(token->content, *s, -1);
			s++;
		}
	}
	if (strcmp(token->content, "") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putnstr_fd(*line, s - *line, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
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
			token->type = LEFT_HER;
			s++;
		}
	}
	*line = s;
	redirect_helper(data, token, line);
}
