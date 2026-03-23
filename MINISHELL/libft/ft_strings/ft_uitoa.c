/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:50 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:43:52 by mtaleb           ###   ########.fr       */
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

char	*ft_uitoa(unsigned int n)
{
	int			len;
	char		*res;
	long int	nb;

	nb = (unsigned long)n;
	len = numberlen(nb);
	res = ft_malloc(len * sizeof(char) + 1);
	if (!res)
		return (NULL);
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
