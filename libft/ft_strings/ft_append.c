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

char	*fappend(char *org, char c)
{
	char	*result;
	size_t	size;

	if (org == NULL)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
	}
	else
	{
		size = ft_strlen(org);
		result = ft_calloc((size + 2), sizeof(char));
		ft_memcpy(result, org, size);
		result[size] = c;
		ft_free(org);
	}
	return (result);
}

// char	*ft_append(char *org, char c, int position)
// {
// 	char	*result;
// 	size_t	size;

// 	if (org == NULL)
// 	{
// 		result = ft_calloc(2, sizeof(char));
// 		result[0] = c;
// 	}
// 	else
// 	{
// 		size = ft_strlen(org);
// 		if (position == -1)
// 			position = size;
// 		result = ft_calloc((size + 2), sizeof(char));
// 		ft_memcpy(result, org, position);
// 		ft_memcpy(result + position, &c, 1);
// 		ft_memcpy(result + position + 1, org + position, size - position);
// 		ft_free(org);
// 	}
// 	return (result);
// }
