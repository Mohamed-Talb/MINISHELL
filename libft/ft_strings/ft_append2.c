/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:06:35 by mtaleb            #+#    #+#             */
/*   Updated: 2025/05/18 08:36:12 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_append2(char **src, char *str, int pos)
{
	char	**ptr;

	int (i), (j);
	if (!src || !str)
		return (NULL);
	ptr = malloc(sizeof(char *) * (ft_strlen2(src) + 2));
	if (!ptr)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (src[j])
	{
		if (i == pos)
		{
			ptr[i] = ft_strdup(str);
			i++;
			continue ;
		}
		ptr[i] = ft_strdup(src[j]);
		if (!ptr[i])
			return (ft_freedouble(&ptr), NULL);
		i++;
		j++;
	}
	if (i == pos)
	{
		ptr[i] = ft_strdup(str);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
