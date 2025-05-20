/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:58 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:31:08 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	x;
	int	y;

	if (!s1 || !set)
		return (NULL);
	x = 0;
	y = ft_strlen(s1) - 1;
	while (!is_set(s1[x], set))
		x++;
	while (!is_set(s1[y], set))
		y--;
	return (ft_substr(s1, x, y - x + 1));
}
