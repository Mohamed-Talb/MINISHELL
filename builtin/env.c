/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:01:14 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:01:23 by mtaleb           ###   ########.fr       */
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
