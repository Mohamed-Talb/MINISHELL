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

void redirect_errors(t_data *data, char *s)
{
	char *er = "";

	if (s[0] == '\0' || in_set(REDIRECTION_SET , s[0]) == 1)
	{
		er = ft_strjoin(er, UNEXPECTED_TOKEN);
		if (s[0] == '\0')
			er = ft_strjoin(er, "newline");
		else if (ft_strncmp(">>", s, 2) == 0)
			er = ft_strjoin(er, ">>");
		else if (ft_strncmp("<<", s, 2) == 0)
			er = ft_strjoin(er, "<<");
		else
			er = ft_append(er, s[0], -1);
		set_errors(data, ft_strjoin(er, "'\n"), 2);
	}
}

int redirect_helper(t_data *data, t_list *token, char *s, int i)
{
	while (ft_iswhitespace(s[i]))
		i++;
	redirect_errors(data, &s[i]);
	while (s[i] != '\0' && in_set(REDIRECTION_SET, s[i]) != 1 && !ft_iswhitespace(s[i]))
	{
		if(s[i] == '"' && (token->type == RIGHT_RED
			|| token->type == LEFT_RED || token->type == RIGHT_HER))
				i = double_q(data, token, s, i);
		if (s[i] == '$' && token->type != LEFT_HER)
			i = expand(data, token->content, s, i);
		else if(s[i] == '\'')
			i = single_q(data, token->content, s, i);
		else
		{
			token->content = ft_append(token->content, s[i], -1);
			i++;
		}
	}
	return (i);
}

int redirect(t_data *data, t_list *token, char *s, int i)
{
	// if(ft_strlen(token->content) != 0)
	// 	ft_lstback(&data->cmd_list, ft_strdup(""));
	// token = ft_lstlast(data->cmd_list); // why is this necessary, you're not even setting the type?
	if (s[i] == '>')
	{
		token->type = RIGHT_RED;
		i++;
		if (s[i] == '>')
		{
			token->type = RIGHT_HER;
			i++;
		}
	}
	else if (s[i] == '<')
	{
		token->type = LEFT_RED;
		i++;
		if (s[i] == '<')
		{
			token->type = LEFT_HER;
			i++;
		}
	}
	return (redirect_helper(data, token, s, i));
}
