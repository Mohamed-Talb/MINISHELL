/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:23 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:30:20 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		p;

	i = 0;
	p = 0;
	if (!s1)
		return (NULL);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[p] = s1[i];
		i++;
		p++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[p++] = s2[i++];
	}
	ptr[p] = 0;
	return (ptr);
}
