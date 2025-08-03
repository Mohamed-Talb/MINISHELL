/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:08:07 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:08:09 by mtaleb           ###   ########.fr       */
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
