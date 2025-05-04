/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:28 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:41 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

char	*ftappend(char *org, char c, int position)
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
	result = ft_calloc((size + 2), sizeof(char));
	ft_memmove(result, org, position);
	ft_memmove(result + position, &c, 1);
	ft_memmove(result + position + 1, org + position, size - position);
	result[size + 1] = 0;
	free(org);
	return (result);
}

long	ftnewatoi(char **nptr)
{
	long	result;

	result = 0;
	while (ft_isdigit(**nptr) && result < 2147483648)
	{
		result = result * 10 + **nptr - '0';
		(*nptr)++;
	}
	return (result);
}
