/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:07:06 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:29:10 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_append(char *org, char c, int position)
{
	char	*result;
	size_t	size;

	if (!org)
	{
		result = ft_calloc(2, sizeof(char));
		ft_memmove(result, &c, 1);
		result[1] = 0;
		return (result);
	}
	size = ft_strlen(org);
	if (position == -1)
		position = size;
	result = ft_calloc((size + 2), sizeof(char));
	ft_memmove(result, org, position);
	ft_memmove(result + position, &c, 1);
	ft_memmove(result + position + 1, org + position, size - position);
	result[size + 1] = 0;
	free(org);
	return (result);
}
