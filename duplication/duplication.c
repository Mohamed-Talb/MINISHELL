/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:01 by kel-mous          #+#    #+#             */
/*   Updated: 2025/07/30 20:13:42 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dupname(t_data *data, char *line)
{
	char	*filename;
	char	*s;

	filename = NULL;
	s = line;
	while (*s)
	{
		// printf("%s\n", filename);
		if (ft_iswhitespace(*s))
		{
			ft_free(line);
			ft_free(filename);
			return (NULL);
			
		}
		else if (*s == '$')
			line = expand(data, line, &s);
		else if (*s == '\'')
			filename = single_q(data, filename, &s);
		else if (*s == '"')
			filename = double_q(data, filename, &s);
		else
			filename = fappend(filename, *s++);
	}
	ft_free(line);
	return (filename);
}

int	getfilename(t_data *data, t_list *node)
{
	char	*filename;

	filename = get_dupname(data, ft_strdup(node->content));
	if (filename == NULL)
	{
		eputf(AMBIGOUS_RED, node->content);
		ft_free(filename);
		return (-1);
	}
	node->content = filename;
	return (0);
}

int	openredfiles(t_data *data, t_list *node)
{
	int	fd;

	if (node->type != LEFT_HER && getfilename(data, node))
		return (-1);
	if (node->type == RIGHT_HER)
		fd = open(node->content, O_RDWR | O_CREAT | O_APPEND, 0644); // why open it as O_RDWR? only one opperation is needed
	else if (node->type == RIGHT_RED)
		fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->content, O_RDONLY);
	if (fd == -1)
	{
		eputf("minishell: %s: %s\n", node->content, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	fds_manager(t_data *data, t_cmds *cmd)
{
	t_list	*curr;
	int		fd;

	curr = cmd->allred;
	while (curr)
	{
		fd = openredfiles(data, curr);
		if (fd < 0)
			return (fd);
		if (curr->type == LEFT_HER || curr->type == LEFT_RED)
		{
			ft_close(cmd->inpipe[0]);
			cmd->inpipe[0] = fd;
		}
		else if (curr->type == RIGHT_RED || curr->type == RIGHT_HER)
		{
			ft_close(cmd->outpipe[1]);
			cmd->outpipe[1] = fd;
		}
		curr = curr->next;
	}
	return (0);
}

int	duplication(t_data *data, t_cmds *cmd)
{
	// ft_close(cmd->inpipe[1]);
	ft_close(cmd->outpipe[0]);
	if (fds_manager(data, cmd) < 0)
		return (-1);
	if (cmd->inpipe[0] != -1)
	{
		dup2(cmd->inpipe[0], 0);
		ft_close(cmd->inpipe[0]);
	}
	if (cmd->outpipe[1] != -1)
	{
		dup2(cmd->outpipe[1], 1);
		ft_close(cmd->outpipe[1]);
	}
	return (1);
}
