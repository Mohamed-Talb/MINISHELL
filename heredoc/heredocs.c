/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:33:25 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/05 12:05:49 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*randomnbr(void)
{
	unsigned int	buff;
	int				fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		eputf("minishell: open: %s\n", (char *[]){strerror(errno)});
		errors(NULL, EXIT_FAILURE);
	}
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
	signal_state(1);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
	{
		eputf("minishell: fork: %s\n", (char *[]){strerror(errno)});
		errors(NULL, EXIT_FAILURE);
	}
	if (id == 0)
	{
		signals();
		fill_herdoc(data, node, rname);
	}
	wait(&status);
	signal_state(0);
	signals();
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
