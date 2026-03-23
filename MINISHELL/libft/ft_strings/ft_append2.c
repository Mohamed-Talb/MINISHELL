/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:41:47 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/29 12:09:25 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	insert(char **dest, char **src, char *str, int pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j])
	{
		if (i == pos)
		{
			dest[i] = ft_strdup(str);
			i++;
			continue ;
		}
		dest[i] = ft_strdup(src[j]);
		i++;
		j++;
	}
	if (i == pos)
	{
		dest[i] = ft_strdup(str);
		i++;
	}
	dest[i] = NULL;
}

char	**ft_append2(char **src, char *str, int pos)
{
	char	**ptr;

	if (!src || !str)
		return (NULL);
	ptr = ft_malloc(sizeof(char *) * (ft_strlen2(src) + 2));
	if (!ptr)
		return (NULL);
	insert(ptr, src, str, pos);
	return (ptr);
}
