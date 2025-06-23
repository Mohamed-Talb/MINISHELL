/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:46:40 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:29:27 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	r;
	int	i;

	i = 0;
	r = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + nptr[i] - '0';
		i++;
	}
	return (r * sign);
}

long	ft_atoy(const char *nptr)
{
	int	sign;
	long	r;
	int	i;

	i = 0;
	r = 0;
	sign = 1;
	while (ft_iswhitespace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + nptr[i] - '0';
		if ((r > INT_MAX && sign == 1) || (r > INT_MAX + 1L && sign == -1))
			return (INT_MAX + 1L);
		i++;
	}
	while (ft_iswhitespace(nptr[i]))
		i++;
	if (nptr[i] != '\0')
		return (INT_MAX + 2L);
	return (r * sign);
}
