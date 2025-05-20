/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:06:59 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:17 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	numberlen(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	if (nb < 0)
		nb = -nb;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*printint(int n, t_flag *params)
{
	char		*res;
	int			len;
	long int	nb;

	nb = (long int)n;
	len = numberlen(nb);
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	res[len] = 0;
	len--;
	if (!nb)
		res[0] = '0';
	else if (nb < 0)
	{
		params->negative = true;
		nb = -nb;
	}
	while (nb)
	{
		res[len--] = (nb % 10 + '0');
		nb = nb / 10;
	}
	return (res);
}
