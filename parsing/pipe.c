/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:48 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 14:45:47 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_errors(t_data *data, char *s, int check_prev)
{
	char	*strerror;
	t_list 	*prev;

	strerror = NULL;
	prev = ft_lstprevlast(data->cmd_list);
	if (check_prev && prev == NULL)
		strerror = mprintf(UNEXPECTED_TOKEN, "|");
	else if (*s == '|')
		strerror = mprintf(UNEXPECTED_TOKEN, "||");
	else
	{
		while (ft_iswhitespace(*s))
			s++;
		if (*s == '|')
			strerror = mprintf(UNEXPECTED_TOKEN, "|");
		else if (*s == '\0')
			strerror = mprintf(UNEXPECTED_TOKEN, "newline");
	}
	if (strerror)
		set_errors(data, strerror, 2);
}

t_list	*hpipe(t_data *data, t_list *token, char **line)
{
	int		check_prev;
	char	*s;
	int		i;

	i = 0;
	s = *line;
	token = creat_node(data);
	check_prev = true;
	while (s + i >= data->line && (ft_iswhitespace(s[i]) || s[i] == s[0]))
	{
		if (s + i <= data->expand_rage)
		{
			check_prev = false;
			break ;
		}
		i--;
	}
	pipe_errors(data, s + 1, check_prev);
	token->content = fappend(token->content, *s++);
	token->type = PIPE;
	token = NULL;
	data->pipes_nb++;
	*line = s;
	return (token);
}
