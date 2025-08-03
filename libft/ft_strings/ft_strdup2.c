/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:06:57 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:06:59 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_strdup2(char **str)
{
	int		i;
	char	**ptr;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	ptr = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (str[i])
	{
		ptr[i] = ft_strdup(str[i]);
		if (!ptr[i])
			return (ft_freedouble(ptr), NULL);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
