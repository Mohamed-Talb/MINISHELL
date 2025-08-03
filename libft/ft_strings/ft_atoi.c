/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:05:59 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:06:02 by mtaleb           ###   ########.fr       */
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

int	atoi_sign(char *nptr)
{
	int	sign;

	sign = 1;
	while (ft_iswhitespace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (!nptr[0])
			return (0);
	}
	else if (!ft_isdigit(*nptr))
		return (0);
	while (ft_isdigit(*nptr))
		nptr++;
	while (ft_iswhitespace(*nptr))
		nptr++;
	if (*nptr != '\0')
		return (0);
	return (sign);
}

unsigned long long	ft_atoi_l(char *nptr)
{
	unsigned long long	result;

	if (atoi_sign(nptr) == 0)
		return (L_OVERFLOW + 1ULL);
	result = 0;
	while (!ft_isdigit(*nptr))
		nptr++;
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - 48;
		nptr++;
	}
	return (result);
}
