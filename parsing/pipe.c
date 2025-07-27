/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:48 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 14:39:49 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void pipe_errors(t_data *data, char c, int check_prev) // this function should be optimized
{
	t_list *prev;
	char *strerror;

	if (check_prev)
		prev = ft_lstprevlast(data->cmd_list);
	if (data->line && data->line[ft_strlen(data->line) - 1] == '|')
		strerror = mprintf(UNEXPECTED_TOKEN, "newline");
	if (c == '|')
		strerror = mprintf(UNEXPECTED_TOKEN, "||");
	else if (check_prev && (data->line[0] == '|' || !ft_strcmp(prev->content, "|")))
		strerror = mprintf(UNEXPECTED_TOKEN, "|");
	else 
		return ;
	set_errors(data, strerror, 2);
}

t_list	*hpipe(t_data *data, t_list *token, char **line)
{
	int check_prev;
	char *s;
	int i;

	i = 0;
	s = *line;
	token = creat_node(data);
	check_prev = true;
	while (s + i >= data->line && (ft_iswhitespace(s[i]) || s[i] == s[0]))
	{
		if (s + i <= data->expand_rage)
		{
			check_prev = false;
			break;
		}
		i--;
	}
	pipe_errors(data, *(s + 1), check_prev); // this still has problems like: " | cat" for which it needs to check prev correctly
	token->content = fappend(token->content, *s++);
	token->type = PIPE;
	token = NULL;
	data->pipes_nb++;
	*line = s;
	return (token);
}
