/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:07:06 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:29:10 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void charappend(char *dest, char c)
{
	int i;

	i = 0;
	while (dest[i] != 0)
		i++;
	dest[i] = c;
	dest[i + 1] = '\0';
}

void strappend(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != 0)
		i++;
	j = 0;
	while (src[j] != 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

char *append(char *org, char c)
{
	char	*result;
	size_t	size;

	if (org == NULL)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
	}
	else
	{
		size = ft_strlen(org);
		result = ft_calloc((size + 2), sizeof(char));
		strappend(result, org);
		charappend(result, c);
	}
	return (result);
}

char *fappend(char *org, char c)
{
	char	*result;
	size_t	size;

	if (org == NULL)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
	}
	else
	{
		size = ft_strlen(org);
		result = ft_calloc((size + 2), sizeof(char));
		strappend(result, org);
		charappend(result, c);
		ft_free(org);
	}
	return (result);
}

char	*pappend(char *org, char c, int position)
{
	char	*result;
	size_t	size;

	if (org == NULL)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
	}
	else
	{
		size = ft_strlen(org);
		if (position == -1)
			position = size;
		result = ft_calloc((size + 2), sizeof(char));
		ft_memcpy(result, org, position);
		ft_memcpy(result + position, &c, 1);
		ft_memcpy(result + position + 1, org + position, size - position);
	}
	return (result);
}

char	*ft_append(char *org, char c, int position)
{
	char	*result;
	size_t	size;

	if (org == NULL)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = c;
	}
	else
	{
		size = ft_strlen(org);
		if (position == -1)
			position = size;
		result = ft_calloc((size + 2), sizeof(char));
		ft_memcpy(result, org, position);
		ft_memcpy(result + position, &c, 1);
		ft_memcpy(result + position + 1, org + position, size - position);
		ft_free(org);
	}
	return (result);
}
