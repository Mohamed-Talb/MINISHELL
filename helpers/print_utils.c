/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:28:59 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 09:29:00 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*margs_printf(char *s, va_list args)
{
	char	*result;

	result = NULL;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (*s == 'c')
				result = fappend(result, va_arg(args, int));
			else if (*s == 'd' || *s == 'i')
				result = ft_strjoin_es(result, ft_itoa(va_arg(args, int)), 3);
			else if (*s == 's')
				result = ft_strjoin_es(result, va_arg(args, char *), 1);
			s++;
		}
		else
			result = fappend(result, *s++);
	}
	return (result);
}

char	*mprintf(char *s, ...)
{
	va_list	args;
	char	*result;

	va_start(args, s);
	result = margs_printf(s, args);
	va_end(args);
	return (result);
}

int	eputf(char *s, ...)
{
	va_list	args;
	char	*result;
	int		len;

	va_start(args, s);
	result = margs_printf(s, args);
	ft_putstr_fd(result, 2);
	len = ft_strlen(result);
	ft_free(result);
	va_end(args);
	return (len);
}

void	errcln(int exitcode, char *error, ...)
{
	char	*result;
	va_list	args;

	if (error)
	{
		va_start(args, error);
		result = margs_printf(error, args);
		ft_putstr_fd(result, 2);
		va_end(args);
		ft_free(result);
	}
	free_all_adresses();
	exit(exitcode);
}
