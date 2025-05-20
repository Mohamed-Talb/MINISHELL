/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:53 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:31:04 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (ft_strlen(s) - 1);
	c = (unsigned char)c;
	if (c == 0)
		return ((char *)(&s[len + 1]));
	while (len >= 0)
	{
		if (s[len] == c)
		{
			return ((char *)(&s[len]));
		}
		len--;
	}
	return (0);
}
