/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:00:21 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:30:10 by mtaleb           ###   ########.fr       */
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
	ptr = malloc(sizeof(char *) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ptr[i] = ft_strdup(str[i]);
		if (!ptr[i])
			return (ft_freedouble(&ptr), NULL);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
