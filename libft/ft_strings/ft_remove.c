/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:17 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:45:35 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_remove(char *str, int pos)
{
	int		i;
	int		j;
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = ft_malloc(ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == pos)
		{
			i++;
			continue ;
		}
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = 0;
	return (ptr);
}
