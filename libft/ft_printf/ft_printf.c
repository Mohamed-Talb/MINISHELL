/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:14:26 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:17:48 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*getformat(const char *format, va_list args, t_flag *params)
{
	char	*ptr;

	ptr = 0;
	if (++(params->specifier) && format[0] == 's')
		ptr = precision(params, printstring(va_arg(args, char *)));
	else if (++(params->specifier) && format[0] == 'u')
		ptr = precision(params, printunsigned(va_arg(args, unsigned int)));
	else if (++(params->specifier) && format[0] == 'x')
		ptr = precision(params, printhexa(va_arg(args, unsigned int),
					"0123456789abcdef", params));
	else if (++(params->specifier) && format[0] == 'X')
		ptr = precision(params, printhexa(va_arg(args, unsigned int),
					"0123456789ABCDEF", params));
	else if (++(params->specifier) && format[0] == 'd')
		ptr = precision(params, printint(va_arg(args, int), params));
	else if (++(params->specifier) && format[0] == 'i')
		ptr = precision(params, printint(va_arg(args, int), params));
	else if (++(params->specifier) && format[0] == 'p')
		ptr = precision(params, printmemory(va_arg(args, void *)));
	return (ptr);
}

static int	parseformat(const char **s, va_list args, t_flag *params)
{
	char	*temp;
	int		res;

	res = 0;
	initflags(params);
	initstruct((char **)s, params);
	if (**s == 'c')
	{
		res = printchar(va_arg(args, int), params->width, params->minus);
		return (res);
	}
	temp = getformat(*s, args, params);
	temp = flags(temp, params);
	res += width(temp, params);
	return (res);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	t_flag	params;
	int		result;

	if (!s || !checkoverflow((char *)s))
		return (-1);
	result = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			if (checkorder((char *)++s) && (*s && *s != '%'))
				result += parseformat(&s, args, &params);
			else
				ft_putchar((result++, '%'));
		}
		else
			ft_putchar((result++, *s));
		s++;
	}
	va_end(args);
	return (result);
}
