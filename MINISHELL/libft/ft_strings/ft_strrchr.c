/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:08:01 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:08:04 by mtaleb           ###   ########.fr       */
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
