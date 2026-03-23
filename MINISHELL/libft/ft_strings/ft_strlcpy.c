/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:07:28 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:07:31 by mtaleb           ###   ########.fr       */
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
