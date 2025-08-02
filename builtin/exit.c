/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:49 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/02 17:39:02 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_checker(unsigned long long value, int sign, char *arg)
{
	if (sign == 0)
	{
		eputf(NUMREQ_ERR, arg);
		return (NUMREQ_CODE);
	}
	if ((value == L_OVERFLOW && sign == 1) || value > L_OVERFLOW)
	{
		eputf(NUMREQ_ERR, arg);
		return (NUMREQ_CODE);
	}
	if (value == L_OVERFLOW && sign == -1)
		value = (LLONG_MIN);
	else
		value = sign * ((long long)value);
	return ((unsigned char)value);
}

int	ft_exit(int argc, char **argv, t_data *data)
{
	int	result;

	if (argc == 1)
		result = data->exit_code;
	else
	{
		result = exit_checker(ft_atoi_l(argv[1]), atoi_sign(argv[1]), argv[1]);
		if (result == NUMREQ_CODE)
		{
			ft_putstr_fd("exit\n", 2);
			free_all_adresses();
			exit(2);
		}
		if (argc > 2)
		{
			eputf(EXCESS_ARGS_ERR);
			return (1);
		}
	}
	ft_putstr_fd("exit\n", 2);
	free_all_adresses();
	exit(result);
}
