/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:48 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:24:36 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_errors(t_data *data, char c, int check_prev)
{
	t_list	*prev;
	char	*strerror;
	int		i;

	strerror = NULL;
	if (check_prev)
	{
		prev = ft_lstprevlast(data->cmd_list);
		if (c == '|')
			strerror = mprintf(UNEXPECTED_TOKEN, "||");
		else if (data->line[0] == '|' || prev == NULL
			|| !ft_strcmp(prev->content, "|"))
			strerror = mprintf(UNEXPECTED_TOKEN, "|");
	}
	if (!strerror)
	{
		i = ft_strlen(data->line) - 1;
		while (ft_iswhitespace(data->line[i]))
			i--;
		if (data->line[i] == '|')
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
	pipe_errors(data, *(s + 1), check_prev);
	token->content = fappend(token->content, *s++);
	token->type = PIPE;
	token = NULL;
	data->pipes_nb++;
	*line = s;
	return (token);
}
