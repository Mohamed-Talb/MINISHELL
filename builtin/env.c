/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:45 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/31 12:02:44 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(int argc, char **argv, t_data *data)
{
	(void)argv;
	if (argc != 1)
	{
		eputf(ARG_ERROR, "env");
		return (1);
	}
	ft_printdoule(data->env);
	return (0);
}
