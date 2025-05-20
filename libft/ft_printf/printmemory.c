/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printmemory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:12:32 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:24 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*memoryhexa(unsigned long n, char *base)
{
	char	*result;

	result = 0;
	while (1)
	{
		result = ftappend(result, base[n % 16], 0);
		n /= 16;
		if (!n)
			break ;
	}
	return (result);
}

char	*printmemory(void *addr)
{
	char	*ptr;

	if (!addr)
		return (NULL);
	ptr = memoryhexa((unsigned long)addr, "0123456789abcdef");
	ptr = ftappend(ptr, 'x', 0);
	ptr = ftappend(ptr, '0', 0);
	return (ptr);
}
