/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:26 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/29 12:11:33 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_remove2(char **str, int index)
{
	int		len;
	char	**new;

	int (i), (j);
	if (!str || !*str)
		return (NULL);
	len = ft_strlen2(str);
	if (index < 0 || index >= len)
		return (NULL);
	new = ft_calloc(len, sizeof(char *));
	(1) && (i = 0, j = 0);
	while (str[i])
	{
		if (i == index)
		{
			ft_free(str[i]);
			i++;
			continue ;
		}
		else
			new[j] = str[i];
		i++;
		j++;
	}
	return (new);
}
