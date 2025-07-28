/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdouble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:01 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:43:02 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printdoule(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putstr(str[i]);
		ft_putchar('\n');
		i++;
	}
}
