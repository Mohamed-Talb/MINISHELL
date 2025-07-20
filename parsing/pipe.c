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

static void pipe_errors(t_data *data, char c)
{
	t_list *prev;
	char *strerror;

	prev = ft_lstprevlast(data->cmd_list);
	if (data->line && data->line[ft_strlen(data->line) - 1] == '|')
	{
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "newline`\n");
		set_errors(data, strerror, 2);
		return;
	}
	if (c == '|')
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "||'\n");
	else if (data->line[0] == '|' || !ft_strcmp(prev->content, "|"))
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "|'\n");
	else 
		return ;
	set_errors(data, strerror, 2);
}


t_list	*hpipe(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	token = creat_node(data);
	pipe_errors(data, *(s + 1));
	token->content = ft_append(token->content, *s++, -1);
	token->type = PIPE;
	token = NULL;
	data->pipes_nb++;
	*line = s;
	return (token);
}
