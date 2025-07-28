/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:40:05 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:35:27 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*unexpected_redirect(char **line, char slot[10])
{
	char	*result;
	char	*s;

	s = *line;
	if (*s == '\0')
		ft_strlcpy(slot, "newline", 10);
	else if (in_set("<>", *s))
	{
		slot[0] = *s++;
		if (in_set("<>", *s))
			slot[1] = *s++;
	}
	else if (*s == '|')
	{
		slot[0] = *s++;
		if (in_set("|", *s))
			slot[1] = *s++;
	}
	else
		return (NULL);
	result = mprintf(UNEXPECTED_TOKEN, slot);
	*line = s;
	return (result);
}

char	*get_realtoken(t_list *token, char **line)
{
	char	*s;

	s = *line;
	while (*s != '\0' && ft_iswhitespace(*s) == false && token->content
		&& !in_set("|><", *s))
	{
		if (*s == '\'')
			token->content = get_enclosed_text(token->content, &s);
		else if (*s == '"')
			token->content = get_enclosed_text(token->content, &s);
		else
			token->content = fappend(token->content, *s++);
	}
	*line = s;
	return (token->content);
}

void	redirect_helper(t_data *data, t_list *token, char **line)
{
	char	slot[10];
	char	*result;
	char	*s;

	s = *line;
	ft_bzero(slot, 10);
	while (ft_iswhitespace(*s))
		s++;
	result = unexpected_redirect(&s, slot);
	if (result != NULL)
		set_errors(data, result, 2);
	if (get_realtoken(token, &s) == NULL)
		set_errors(data, UNCLOSED_ERROR, 2);
	*line = s;
}

void	redirection(t_data *data, t_list *token, char **line)
{
	char	*s;

	if (ft_strlen(token->content) != 0 || token->type != 0)
		ft_lstback(&data->cmd_list, ft_strdup(""));
	token = ft_lstlast(data->cmd_list);
	s = *line;
	if (*s++ == '>')
	{
		token->type = RIGHT_RED;
		if (*s == '>')
		{
			token->type = RIGHT_HER;
			s++;
		}
	}
	else if (*s++ == '<')
	{
		token->type = LEFT_RED;
		if (*s == '<')
		{
			token->type = LEFT_HER;
			s++;
		}
	}
	redirect_helper(data, token, &s);
	*line = s;
}
