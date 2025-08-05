/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:28:59 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/05 12:03:21 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mprintf(char *s, char **args)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (*s)
	{
		if (*s == '%' && s[1] == 's')
		{
			s++;
			result = ft_strjoin_es(result, args[i++], 1);
		}
		else
			result = fappend(result, *s);
		s++;
	}
	return (result);
}

int	eputf(char *s, char **args)
{
	char	*result;
	size_t	len;

	result = mprintf(s, args);
	ft_putstr_fd(result, 2);
	len = ft_strlen(result);
	ft_free(result);
	return (len);
}
