/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printunsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:53:02 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:34 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	numberlen(unsigned long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*printunsigned(unsigned int n)
{
	int			len;
	char		*res;
	long int	nb;

	nb = (unsigned long)n;
	len = numberlen(nb);
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (0);
	res[len] = 0;
	len--;
	if (!nb)
		res[0] = '0';
	while (nb)
	{
		res[len--] = (nb % 10 + '0');
		nb = nb / 10;
	}
	return (res);
}
