/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillherdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:58:13 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/29 12:13:22 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expanded_line(t_data *data, char **line)
{
	char	*newline;
	char	*s;

	s = *line;
	newline = ft_strdup("");
	while (*s)
	{
		if (*s == '$')
		{
			if (s[1] == '\'' || s[1] == '"')
				newline = fappend(newline, *s++);
			else
				*line = expand(data, *line, &s);
		}
		else
			newline = fappend(newline, *s++);
	}
	ft_free(*line);
	return (newline);
}

static void	handle_lines(t_data *data, t_list *node, int fd, char *del)
{
	char	*line;

	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
		{
			eputf(HEREDOC_EOF, del);
			break ;
		}
		if (ft_strcmp(del, line) == 0)
		{
			ft_free(line);
			break ;
		}
		if (hasfrom_set(node->content, "'\"") == false)
			line = get_expanded_line(data, &line);
		ft_putendl_fd(line, fd);
		ft_free(line);
	}
}

void	fill_herdoc(t_data *data, t_list *node, char *rname)
{
	char	*delemiter;
	int		fd;

	fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
	if (fd < 0)
	{
		eputf("minishell: open: %s\n", strerror(errno));
		errors(NULL, EXIT_FAILURE);
	}
	delemiter = getdelemiter(node->content);
	handle_lines(data, node, fd, delemiter);
	errors(NULL, 0);
	close(fd);
}
