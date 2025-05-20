/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:53:52 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:12 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*printhexa(unsigned int n, char *base, t_flag *params)
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
	if (result[0] == '0')
		params->hashtag = false;
	return (result);
}
