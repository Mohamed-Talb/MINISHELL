/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:45 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:17:37 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	inset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return ((1));
		i++;
	}
	return ((0));
}

int	checkorder(char *s)
{
	size_t	i;

	i = 0;
	while (inset(s[i], "-+ #0"))
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (inset(s[i], "%cspdiuxX"))
		return (1);
	return (0);
}

char	*checknull(t_flag *params)
{
	params->zero = false;
	if (params->specifier == 2 && params->precision < 6 && params->precision)
		return (ft_strdup(""));
	if (params->specifier == 2)
		return (ft_strdup("(null)"));
	if (params->specifier == 8)
		return (ft_strdup("(nil)"));
	return (NULL);
}

int	checkoverflow(char *s)
{
	while (*s)
	{
		if (*s == '%' && checkorder(++s))
		{
			while (*s && (!ft_isdigit(*s) || *s == '0'))
				s++;
			if (*s && ft_isdigit(*s) && ftnewatoi(&s) > 2147483647)
				return (0);
			if (*s && *s == '.' && ft_isdigit(*(++s + 1))
				&& ftnewatoi(&s) > 2147483647)
				return (0);
		}
		s++;
	}
	return (1);
}
