/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:16:39 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 17:38:33 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_cmds(t_data *data)
{
	int	i;

	if (data->cmds)
	{
		i = 0;
		while (data->cmds[i])
		{
			if (data->cmds[i]->flags)
				ft_freedouble(data->cmds[i]->flags);
			if (data->cmds[i]->allred)
				ft_lstclear(&data->cmds[i]->allred);
			ft_free(data->cmds[i]->cmd);
			ft_free(data->cmds[i]->error);
			ft_free(data->cmds[i]);
			i++;
		}
		ft_free(data->cmds);
		data->cmds = NULL;
	}
}

void	reset_data(t_data *data)
{
	if (data == NULL)
		return ;
	clean_cmds(data);
	if (data->cmd_list != NULL)
	{
		ft_lstclear(&data->cmd_list);
		data->cmd_list = NULL;
	}
	if (data->line != NULL)
	{
		ft_free(data->line);
		data->line = NULL;
	}
	data->expand_rage = NULL;
	data->pipes_nb = 1;
}
