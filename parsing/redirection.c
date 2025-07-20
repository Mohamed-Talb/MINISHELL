/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:40:05 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 14:40:06 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redirect_errors(t_data *data, char **line)
{
	char *er = "";
	char *s;
	int  i = 0;

	s = *line;
	if (*s == '\0' || in_set(REDIRECTION_SET , *s) == true)
	{
		er = ft_strjoin(er, UNEXPECTED_TOKEN);
		if (*s == '\0')
			er = ft_strjoin(er, "newline");
		else
		{
			while (i < 2 && in_set(REDIRECTION_SET , *s))
			{
				er = ft_append(er, *s, -1);
				i++;
				s++;
			}
		}
		set_errors(data, ft_strjoin(er, "'\n"), 2);
		*line = s;
		return (1);
	}
	return (0);
}

int get_enclosed_text(t_list *token, char **line)
{
	char target;
	char *s;

	s = *line;
	target = *s;
	token->content = fappend(token->content, *s++);
	while (true)
	{
		if (*s == '\0')
			return (1);
		if (*s == target)
		{
			token->content = fappend(token->content, *s++);
			break;
		}
		token->content = fappend(token->content, *s++);
	}
	*line = s;
	return (0);
}

int get_realtoken(t_list *token, char **line)
{
	char *s;
	int value;

	value = 0;
	s = *line;
	while (*s != '\0' && ft_iswhitespace(*s) == false && value == 0)
	{
		if (*s == '\'')
			value = get_enclosed_text(token, &s);
		else if (*s == '"')
			value = get_enclosed_text(token, &s);
		else
			token->content = fappend(token->content, *s++);
	}
	*line = s;
	return (value);
}

void redirect_helper(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	redirect_errors(data, &s);
	if (token->type == LEFT_HER && get_realtoken(token, &s))
		set_errors(data, UNCLOSED_ERROR, 2);
	else
	{
		while (*s != '\0' && !in_set(REDIRECTION_SET, *s) && !ft_iswhitespace(*s)) // expand is included in the other forms of redirection, with exeptions like expand inside expand
		{
			if(*s == '"')
				double_q(data, token, &s, 1);
			else if(*s == '\'')
				single_q(data, token, &s);
			else
				token->content = fappend(token->content, *s++);
		}
	}
	*line = s;
}

void redirection(t_data *data, t_list *token, char **line)
{
	char *s;

	if(ft_strlen(token->content) != 0 || token->type != 0)
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
	redirect_helper(data, token, &s);
	*line = s;
}
