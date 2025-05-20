/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:06:35 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 20:06:56 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_append2(char **src, char *str, int pos)
{
	char	**ptr;

	int (i), (j);
	if (!str)
		return (NULL);
	ptr = malloc(sizeof(char *) * (ft_strlen2(src) + 2));
	if (!ptr)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (src[j])
	{
		if (i == pos - 1)
		{
			ptr[i] = ft_strdup(str);
			i++;
			continue ;
		}
		ptr[i] = ft_strdup(src[j]);
		if (!ptr[i])
			return (ft_freedouble(&ptr), NULL);
		i++;
		j++;
	}
	ptr[i] = NULL;
	return (ft_freedouble(&src), ptr);
}
// int main()
// {
//     char **ptr1 = ft_split("echo hello wold if i need", ' ');
//     int i = 0;
//     while(ptr1[i])
//     {
//         printf("%s\n", ptr1[i]);
//         i++;
//     }
//     i = 0;
//     char **ptr = ft_append2(ptr1, "-e", 2);
//     while(ptr[i])
//     {
//         printf("%s\n", ptr[i]);
//         i++;
//     }
// }