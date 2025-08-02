/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:52 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/02 16:39:27 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_enclosed_text(char *token, char **line)
{
	char	target;
	char	*s;

	s = *line;
	target = *s;
	token = fappend(token, *s++);
	while (true)
	{
		if (*s == '\0')
			return (NULL);
		if (*s == target)
		{
			token = fappend(token, *s++);
			break ;
		}
		token = fappend(token, *s++);
	}
	*line = s;
	return (token);
}

char	*geth_enclosed_text(char *token, char **line)
{
	char	target;
	char	*s;

	s = *line;
	target = *s++;
	while (true)
	{
		if (*s == '\0')
			return (NULL);
		if (*s == target)
		{
			s++;
			break ;
		}
		token = fappend(token, *s++);
	}
	*line = s;
	return (token);
}

char	*single_q(t_data *data, char *token, char **line)
{
	char	*s;

	s = *line + 1;
	while ((*s != '\0' || s < data->expand_rage) && *s != '\'')
	{
		token = fappend(token, *s);
		s++;
	}
	if (*s == '\'')
		s++;
	else
		set_errors(data, UNCLOSED_ERROR, 2);
	*line = s;
	return (token);
}

char	*double_q(t_data *data, char *token, char **start, char **line)
{
	char	*s;

	s = *line;
	s++;
	while ((*s != '"' || s < data->expand_rage) && *s != 0)
	{
		if (*s == '$' && *(s + 1) != '"' && s >= data->expand_rage)
			*start = expand(data, *start, &s);
		else
		{
			token = fappend(token, *s);
			s++;
		}
	}
	if (*s == '"')
		s++;
	else
		set_errors(data, UNCLOSED_ERROR, 2);
	*line = s;
	return (token);
}
