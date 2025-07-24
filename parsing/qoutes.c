/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:52 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 14:39:53 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void single_q(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line + 1;
	while (*s != '\0' && *s != '\'')
	{
		token->content = fappend(token->content, *s);
		s++;
	}
	if (*s == '\'')
		s++;
	else
		set_errors(data, UNCLOSED_ERROR, 2);
	*line = s;
}

void double_q(t_data *data, t_list *token, char **line, int state)
{
	char *s;
	
	s = *line;
	s++;
	while(*s != '"' && *s != 0)
	{
		if(*s == '$' && state == 1 && *(s + 1) != '"' && s >= data->expand_rage)
			expand(data, &s);
		else
		{
			token->content = fappend(token->content, *s);
			s++;
		}
	}
	if (*s == '"')
		s++;
	else
		set_errors(data, UNCLOSED_ERROR, 2);
	*line = s;
}
