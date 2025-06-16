#include "../minishell.h"

int	single_q(t_data *data, t_list *token, char *s, int i)
{
	if (s[i] == '\'')
		i++;
	while (s[i] != 0 && s[i] != '\'')
	{
		token->content = ft_append(token->content, s[i], -1);
		i++;
	}
	if (s[i] == '\'')
		i++;
	else
		set_errors(data, "minishell: syntax error: unclosed quote\n", 1);
	return (i);
}

int	double_q(t_data *data, t_list *token, char *s, int i)
{
	if (s[i] == '"')
		i++;
	while (s[i] != 0 && s[i] != '"')
	{
		token->content = ft_append(token->content, s[i], -1);
		i++;
	}
	if (s[i] == '"')
		i++;
	else
		set_errors(data, "minishell: syntax error: unclosed quote\n", 1);
	return (i);
}

int double_qex(t_data *data, t_list *token, char *s, int i)
{
	if (s[i] == '"')
		i++;
	while(s[i] != '"' && s[i] != 0)
	{
		if(s[i] == '$')
		{
			i = expand(data, token->content, s, i);
		}
		else
		{
			token->content = ft_append(token->content, s[i], -1);
			i++;
		}
	}
	if (s[i] == '"')
		i++;
	else
		set_errors(data, "minishell: syntax error: unclosed quote\n", 1);
	return (i);
}
