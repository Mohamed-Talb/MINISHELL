/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:13:51 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:04 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*persicionstr(int digits, char *str)
{
	char	*result;

	result = ft_calloc((digits + 1), sizeof(char));
	ft_memmove(result, str, digits);
	result[digits] = 0;
	free(str);
	return (result);
}

static char	*precisionnbr(int digits, char *str)
{
	size_t	len;
	char	*result;

	len = ft_strlen(str);
	result = ft_calloc((digits + 1), sizeof(char));
	ft_memset(result, '0', digits);
	ft_memmove(result + (digits - len), str, len + 1);
	free(str);
	return (result);
}

char	*precision(t_flag *params, char *str)
{
	char	*result;
	size_t	len;
	size_t	digits;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = str;
	digits = params->precision;
	if (digits || params->precision_exist)
	{
		params->zero = false;
		if (digits > len && params->specifier > 2)
			return (precisionnbr(digits, str));
		else if (!digits && params->specifier > 2 && params->specifier < 8
			&& str[0] == '0' && str[1] == '\0')
		{
			free(str);
			return (ft_strdup(""));
		}
		if (digits < len && params->specifier == 2)
			return (persicionstr(digits, str));
	}
	return (result);
}
