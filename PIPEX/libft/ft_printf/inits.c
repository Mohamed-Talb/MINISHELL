/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:50:55 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:17:53 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	initstruct(char **str, t_flag *params)
{
	while (**str && (**str == '-' || **str == '+' || **str == ' '
			|| **str == '#' || **str == '0'))
	{
		if (**str == '+')
			params->plus = true;
		else if (**str == '-')
			params->minus = true;
		else if (**str == ' ')
			params->space = true;
		else if (**str == '#')
			params->hashtag = true;
		else if (**str == '0')
			params->zero = true;
		(*str)++;
	}
	params->width = ftnewatoi(str);
	if (**str == '.')
	{
		params->precision_exist = true;
		(*str)++;
		params->precision = ftnewatoi(str);
	}
	return (0);
}

void	initflags(t_flag *params)
{
	if (params != NULL)
	{
		params->zero = false;
		params->minus = false;
		params->plus = false;
		params->precision = 0;
		params->width = 0;
		params->space = false;
		params->hashtag = false;
		params->specifier = 1;
		params->precision_exist = false;
		params->negative = false;
	}
}
