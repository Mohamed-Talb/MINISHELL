/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:16:39 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/31 11:57:18 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trach(t_data *data)
{
	int	i;

	if (data->cmds)
	{
		i = 0;
		while (data->cmds[i])
		{
			ft_free(data->cmds[i]->cmd);
			ft_free(data->cmds[i]);
			i++;
		}
		ft_free(data->cmds);
		data->cmds = NULL;
	}
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
}

void	reset_data(t_data *data)
{
	if (data == NULL)
		return ;
	trach(data);
	data->expand_rage = NULL;
	data->pipes_nb = 1;
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		reset_data(data);
		ft_free(data);
		data = NULL;
	}
}
