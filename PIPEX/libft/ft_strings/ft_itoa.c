/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:08:06 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:29:47 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	num_len(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i++;
		nb = -nb;
	}
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			len;
	long int	nb;

	nb = (long int)n;
	len = num_len(nb);
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	res[len] = 0;
	len--;
	if (!nb)
		res[0] = '0';
	else if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		res[len--] = (nb % 10 + '0');
		nb = nb / 10;
	}
	return (res);
}
