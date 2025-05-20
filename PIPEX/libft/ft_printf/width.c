/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:56:22 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/04 15:18:46 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	shiftright(char *ptr, t_flag *params, char c, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if ((ptr[0] == '+' || ptr[0] == '-' || ptr[0] == ' ') && c == '0')
	{
		ft_putchar(ptr[0]);
		count++;
		ptr++;
	}
	if ((ptr[0] == '0' && ptr[1] == 'x') && c == '0')
	{
		ft_putstr("0x");
		ptr += 2;
		count += 2;
	}
	while (params->width-- > len)
	{
		ft_putchar(c);
		count++;
	}
	while (ptr[i])
		ft_putchar((count++, ptr[i++]));
	return (count);
}

static int	shiftleft(char *ptr, t_flag *params, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ptr[i])
	{
		ft_putchar(ptr[i++]);
		count++;
		params->width--;
	}
	while (params->width > 0)
	{
		ft_putchar(c);
		params->width--;
		count++;
	}
	return (count);
}

int	width(char *ptr, t_flag *params)
{
	int	len;

	if (!ptr)
	{
		ptr = checknull(params);
	}
	len = ft_strlen(ptr);
	if (params->width > len)
	{
		if (!params->minus && params->zero)
			len = shiftright(ptr, params, '0', len);
		else if (!params->minus)
			len = shiftright(ptr, params, ' ', len);
		else
			len = shiftleft(ptr, params, ' ');
	}
	else
	{
		ft_putstr(ptr);
	}
	free(ptr);
	return (len);
}
