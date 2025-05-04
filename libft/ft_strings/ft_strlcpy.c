/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:32 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:30:35 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size != 0)
	{
		while (i < size - 1)
		{
			if (src[i])
			{
				dst[i] = src[i];
				i++;
			}
			else
			{
				break ;
			}
		}
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
