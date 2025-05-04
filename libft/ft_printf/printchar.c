/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:21:30 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:08 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	printchar(int c, int width, bool minus)
{
	int	count;

	count = 1;
	if (!minus)
	{
		while (width > 1)
		{
			ft_putchar(' ');
			width--;
			count++;
		}
		ft_putchar(c);
	}
	else
	{
		ft_putchar(c);
		while (width > 1)
		{
			ft_putchar(' ');
			width--;
			count++;
		}
	}
	return (count);
}
