#include "../minishell.h"

void redirect_errors(t_data *data, char c)
{
	char *er = "";


	if (c == '\0' || in_set(REDIRECTION_SET , c) == 1)
	{
		er = ft_strjoin(er, UNEXPECTED_TOKEN);
		if (c == '\0')
			er = ft_strjoin(er, "newline");
		else
			er = ft_append(er, c, -1);
		set_errors(data, ft_strjoin(er, "'\n"), 2);
	}
}

void redirect_helper(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	redirect_errors(data, *s);
	while (*s != '\0' && !in_set(REDIRECTION_SET, *s) && !ft_iswhitespace(*s))
	{
		if(*s == '"' && token->type != LEFT_HER)
			double_q(data, token, &s, 1);
		if (*s == '$' && token->type != LEFT_HER)
			expand(data, token, &s, 0);
		else if(*s == '\''  && token->type != LEFT_HER)
			single_q(data, token, &s);
		else
		{
			token->content = ft_append(token->content, *s, -1);
			s++;
		}
	}
	*line = s;
}

void redirection(t_data *data, t_list *token, char **line)
{
	char *s;

	if(ft_strlen(token->content) != 0)
		ft_lstback(&data->cmd_list, ft_strdup(""));
	token = ft_lstlast(data->cmd_list);
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
	while (ft_iswhitespace(*s))
		s++;
	*line = s;
	redirect_helper(data, token, line);
}
