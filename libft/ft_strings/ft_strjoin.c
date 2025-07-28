/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:54:23 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 10:46:50 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		p;

	i = 0;
	p = 0;
	if (!s1)
		return (NULL);
	ptr = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		ptr[p] = s1[i];
		i++;
		p++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[p++] = s2[i++];
	}
	ptr[p] = 0;
	return (ptr);
}

char	*ft_strjoin_fc(char *str, char *buff, int choice)
{
	char	*new;

	if (!str || !buff)
		return (NULL);
	new = ft_strjoin(str, buff);
	if (choice == 1 || choice == 3)
		ft_free(str);
	if (choice == 2 || choice == 3)
		ft_free(buff);
	return (new);
}

char	*ft_strjoin_es(char *str, char *buff, int choice)
{
	char	*new;

	if (!str && !buff)
		new = ft_strjoin("", "");
	else if (!str)
		new = ft_strjoin("", buff);
	else if (!buff)
		new = ft_strjoin(str, "");
	else
		new = ft_strjoin(str, buff);
	if (choice == 1 || choice == 3)
		ft_free(str);
	if (choice == 2 || choice == 3)
		ft_free(buff);
	return (new);
}
