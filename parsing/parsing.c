/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:42 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 14:45:21 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int parsing_errors(t_data *data, t_list *list)
{
	if (!list)
	{
		reset_data(data);
		return (1);
	}
	while (list)
	{
		if (list->error)
		{
			ft_putstr_fd(list->error, 2);
			reset_data(data);
			return (1);
		}
		list = list->next;
	}
	return 0;
}

static t_list	*regular_parse(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	if (token == NULL)
		token = creat_node(data);
	if (s >= data->expand_rage)
	{
		if (*s == '\'')
			single_q(data, token, &s);
		else if (*s == '"')
			double_q(data, token, &s, 1);
		else if (*s == '<' || *s == '>')
			redirection(data, token, &s);
		else
			token->content = ft_append(token->content, *s++, -1);
	}
	else
		token->content = ft_append(token->content, *s++, -1);
	*line = s;
	return (token);
}

t_list *handle_arg(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	while (*s != '\0' && ft_iswhitespace(*s) == false)
	{
		if (*s == '$' && s >= data->expand_rage)
			expand(data, &s);
		else if (*s == '|' && s >= data->expand_rage)
			token = hpipe(data, token, &s);
		else
			token = regular_parse(data, token, &s);
	}
	*line = s;
	return (token);
}

int parser(t_data *data, char *line)
{
	t_list	*new;
	int		new_pipe;

	new_pipe = 1;
	while (*line != '\0')
	{
		if (ft_iswhitespace(*line) == false)
		{
			new = handle_arg(data, NULL, &line);
			if (new != NULL)
			{
				if (new->content != NULL && new->type != PIPE && new_pipe == 1)
				{
					data->command_count++;
					new_pipe = 0;
				}
				else
					new_pipe = 1;
			}
		}
		else
			line++;
	}
	return (parsing_errors(data, data->cmd_list) == 1);
}
