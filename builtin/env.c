/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:45 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/19 10:34:46 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(int argc, char **argv, t_data *data)
{
	(void)argv;
	if (argc != 1)
	{
		return (1);
	}
	ft_printdoule(data->env);
	return (0);
}
