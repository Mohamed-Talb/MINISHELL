/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:38:01 by kel-mous          #+#    #+#             */
/*   Updated: 2025/07/28 11:38:34 by kel-mous         ###   ########.fr       */
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
			filename = fappend(filename, *s);
		s++;
	}
	ft_free(line);
	return (filename);
}

void	getfilename(t_data *data, t_list *node)
{
	char	*filename;

	filename = get_dupname(data, ft_strdup(node->content));
	if (filename == NULL)
	{
		eputf(AMBIGOUS_RED, node->content);
		errors(NULL, 1);
	}
	node->content = filename;
}

int	openredfiles(t_data *data, t_list *node)
{
	int	fd;

	if (node->type != LEFT_HER)
		getfilename(data, node);
	if (node->type == RIGHT_HER)
		fd = open(node->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (node->type == RIGHT_RED)
		fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->content, O_RDONLY);
	if (fd == -1)
	{
		eputf("minishell: %s: %s\n", node->content, strerror(errno));
		errors(NULL, 1);
	}
	return (fd);
}

void	fds_manager(t_data *data, t_cmds *cmd)
{
	t_list	*curr;
	int		fd;

	curr = cmd->allred;
	while (curr)
	{
		fd = openredfiles(data, curr);
		if (curr->type == LEFT_HER || curr->type == LEFT_RED)
		{
			close(cmd->infd);
			cmd->infd = fd;
		}
		else if (curr->type == RIGHT_RED || curr->type == RIGHT_HER)
		{
			close(cmd->outfd);
			cmd->outfd = fd;
		}
		curr = curr->next;
	}
}

int	duplication(t_data *data, t_cmds *cmd)
{
	fds_manager(data, cmd);
	if (cmd->infd != -1)
	{
		dup2(cmd->infd, 0);
		close(cmd->infd);
	}
	if (cmd->outfd != -1)
	{
		dup2(cmd->outfd, 1);
		close(cmd->outfd);
	}
	return (0);
}
