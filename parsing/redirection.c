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

void checkerrors(t_data *data, char c)
{
	if (c == '\0' || in_set(REDIRECTION_SET , c) == 0)
	{
		ft_putstr_fd(UNEXPECTED_TOKEN, 2);
		if (c == '\0')
			ft_putstr_fd("newline", 2);
		else
			ft_putchar_fd(c, 2);
		errors(data, "'\n", 1);
	}
}

void redirect_helper(t_data *data, t_dlist *token, char **line)
{
	char *s;
	
	while (ft_iswhitespace(**line))
		(*line)++;
	s = *line;
	checkerrors(data, *s);
	while (!(*s == '\0' || in_set(REDIRECTION_SET, *s) == 0 || ft_iswhitespace(*s)))
	{
		if(*s == '"')
			if (token->type == RIGHT_RED || token->type == LEFT_RED || token->type == RIGHT_HER)
				double_q(data, token, &s, 1);
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
	*line = s;
}


void redirect(t_data *data, t_dlist *token, char **line)
{
	char *s;

	if(ft_strlen(token->content) != 0)
		ft_dlstback(&data->cmd_list, ft_strdup(""));
	token = ft_dlstlast(data->cmd_list);
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
