/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:43:42 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:47:06 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	in_set(char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	posin_set(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	hasfrom_set(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in_set(set, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	respects_set(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in_set(set, str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
