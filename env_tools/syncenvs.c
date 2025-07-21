/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncenvs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:37:42 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 13:39:14 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sync_envs(t_data *data)
{
	int	i;
	int	name_len;

	i = 0;
	if (data->env != NULL)
		ft_freedouble(data->env);
	data->env = ft_strdup2(data->exported);
	while (data->env[i])
	{
		name_len = varname_size(data->env[i]);
		if (data->env[i][name_len] != '=')
		{
			data->env = envrm(data->env, data->env[i]);
			continue ;
		}
		i++;
	}
}
