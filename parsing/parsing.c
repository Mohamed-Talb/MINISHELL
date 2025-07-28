/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:42 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:34:37 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parsing_errors(t_list *list)
{
	if (!list)
		return (1);
	while (list)
	{
		if (list->error)
		{
			ft_putstr_fd(list->error, 2);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

static t_list	*regular_parse(t_data *data, t_list *token, char **line)
{
	char	*s;

	s = *line;
	if (token == NULL)
		token = creat_node(data);
	if (s >= data->expand_rage)
	{
		if (*s == '\'')
			token->content = single_q(data, token->content, &s);
		else if (*s == '"')
			token->content = double_q(data, token->content, &s);
		else if (*s == '<' || *s == '>')
			redirection(data, token, &s);
		else
			token->content = fappend(token->content, *s++);
	}
	else
		token->content = fappend(token->content, *s++);
	*line = s;
	return (token);
}

t_list	*handle_arg(t_data *data, char **line)
{
	t_list	*token;
	char	*s;

	s = *line;
	token = NULL;
	while (*s != '\0' && ft_iswhitespace(*s) == false)
	{
		if (*s == '$' && s >= data->expand_rage)
			data->line = expand(data, data->line, &s);
		else if (*s == '|' && s >= data->expand_rage)
			token = hpipe(data, token, &s);
		else
			token = regular_parse(data, token, &s);
	}
	*line = s;
	return (token);
}

int	parser(t_data *data, char *line)
{
	t_list	*new;
	int		new_pipe;
	int		cmd_count;

	new_pipe = 1;
	cmd_count = 0;
	while (*line != '\0')
	{
		if (ft_iswhitespace(*line) == false)
		{
			new = handle_arg(data, &line);
			if (new != NULL)
			{
				if (new->content != NULL && new->type != PIPE && new_pipe == 1)
				{
					cmd_count++;
					new_pipe = 0;
				}
				else
					new_pipe = 1;
			}
		}
		else
			line++;
	}
	return (parsing_errors(data->cmd_list) || cmd_count == 0);
}
