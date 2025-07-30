/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:33:25 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/29 12:13:28 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*randomnbr(void)
{
	unsigned int	buff;
	int				fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		errcln(EXIT_FAILURE, "minishell: open: %s\n", strerror(errno));
	read(fd, &buff, 4);
	ft_close(fd);
	return (ft_uitoa(buff));
}

int	heredoc(t_data *data, t_list *node)
{
	int		status;
	char	*rname;
	int		id;

	rname = ft_strjoin_fc("/tmp/herdoc_", randomnbr(), 2);
	eputf("rname is: %s\n", rname);
	signal(SIGINT, SIG_IGN);
	signal_state(1);
	id = fork();
	if (id == -1)
	{
		eputf("minishell: fork: %s\n", strerror(errno));
		errors(NULL, EXIT_FAILURE);
	}
	if (id == 0)
	{
		signals();
		fill_herdoc(data, node, rname);
	}
	wait(&status);
	(signals(), signal_state(0));
	// ft_free(rname);
	// ft_lstclear(&data->cmd_list);
	// exit(0);
	ft_free(node->content);
	node->content = rname;
	data->exit_code = exitestatus(status);
	return (data->exit_code);
}

int	openallherdocs(t_data *data)
{
	t_list	*allred;
	int		i;

	i = 0;
	while (data->cmds[i])
	{
		allred = data->cmds[i]->allred;
		while (allred)
		{
			if (allred->type == LEFT_HER)
			{
				if (heredoc(data, allred) != 0)
					return (1);
			}
			allred = allred->next;
		}
		i++;
	}
	return (0);
}
