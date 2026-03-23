/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:06:12 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:06:14 by mtaleb           ###   ########.fr       */
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
