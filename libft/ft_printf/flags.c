/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:49:57 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:17:42 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*flags(char *ptr, t_flag *params)
{
	if (!ptr)
		return (NULL);
	if (params->negative == true)
		return (ftappend(ptr, '-', 0));
	else if (params->plus && !params->negative && params->specifier > 5)
	{
		return (ftappend(ptr, '+', 0));
	}
	else if (params->space && !params->negative && !params->plus
		&& params->specifier > 5 && ptr[0] != ' ')
	{
		return (ftappend(ptr, ' ', 0));
	}
	else if (params->hashtag && params->specifier == 4)
	{
		ptr = ftappend(ptr, '0', 0);
		return (ftappend(ptr, 'x', 1));
	}
	else if (params->hashtag && params->specifier == 5)
	{
		ptr = ftappend(ptr, '0', 0);
		return (ftappend(ptr, 'X', 1));
	}
	return (ptr);
}
