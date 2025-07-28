/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:16:33 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 09:16:34 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*init_data(char **penv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->exported = ft_strdup2(penv);
	sync_envs(data);
	data->pipes_nb = 1;
	return (data);
}

int	init_cmds(t_data *data)
{
	int	i;

	data->cmds = ft_calloc((data->pipes_nb + 1), sizeof(t_cmds *));
	i = 0;
	while (i < data->pipes_nb)
	{
		data->cmds[i] = ft_calloc(1, sizeof(t_cmds));
		data->cmds[i]->infd = -1;
		data->cmds[i]->outfd = -1;
		i++;
	}
	data->cmds[i] = NULL;
	return (0);
}
