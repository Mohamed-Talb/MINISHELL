/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:32:03 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/24 17:39:39 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	len;

	if (nmemb != 0 && size > __SIZE_MAX__ / nmemb)
		return (NULL);
	len = nmemb * size;
	ptr = ft_malloc(nmemb * size);
	ft_bzero(ptr, len);
	return (ptr);
}
