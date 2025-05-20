/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:07 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:29:51 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	in_word;
	int	n;

	i = 0;
	in_word = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != c)
		{
			if (!in_word)
			{
				in_word = 1;
				n++;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (n);
}

static void	free_ptrs(char ***ptr, size_t f)
{
	while (f > 0)
	{
		free(*ptr[f]);
		f--;
	}
	free(*ptr);
	ptr = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	ptr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!ptr || !s)
		return (NULL);
	while (k < count_words(s, c))
	{
		i = 0;
		while (s[j] == c)
			j++;
		while (s[j + i] != c && s[j + i])
			i++;
		ptr[k] = ft_substr(s, j, i);
		if (!ptr[k])
			return (free_ptrs(&ptr, k - 1), NULL);
		j += i;
		k++;
	}
	ptr[k] = 0;
	return (ptr);
}
