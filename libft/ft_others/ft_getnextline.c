/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:14:23 by mtaleb            #+#    #+#             */
/*   Updated: 2025/03/05 17:11:03 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strjoinget(char *s1, char *s2)
{
	int		len1;
	int		i;
	char	*returned;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	returned = malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (!returned)
		return (free(s1), free(s2), NULL);
	while (s1[i])
	{
		returned[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		returned[len1 + i] = s2[i];
		i++;
	}
	returned[len1 + i] = '\0';
	free(s1);
	return (returned);
}

void	allocation(char **stored, char **allocated)
{
	if (!*stored)
	{
		*stored = ft_strdup("");
		if (!*stored)
			*stored = NULL;
	}
	*allocated = malloc((size_t)BUFFER_SIZE + 1);
	if (!*allocated)
	{
		if (*stored)
			free(*stored);
		*stored = NULL;
	}
}

void	fireforce(char **stored, char **allocated)
{
	if (*stored)
	{
		free(*stored);
		*stored = NULL;
	}
	if (*allocated)
	{
		free(*allocated);
		*allocated = NULL;
	}
}

char	*returned_line(char **stored, int readen)
{
	char	*temp_saved;
	char	*pos;

	if (readen > 0)
	{
		temp_saved = *stored;
		pos = ft_strchr(temp_saved, '\n');
		if (*(pos + 1))
			*stored = ft_strdup(pos + 1);
		else
			*stored = NULL;
		*(pos + 1) = '\0';
		return (temp_saved);
	}
	temp_saved = ft_strdup(*stored);
	free(*stored);
	*stored = NULL;
	return (temp_saved);
}

char	*ft_getnextline(int fd)
{
	char		*allocated;
	int			readen;
	static char	*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	allocation(&stored, &allocated);
	if (!stored || !allocated)
		return (fireforce(&stored, &allocated), NULL);
	readen = 1;
	while (!(ft_strchr(stored, '\n')) && readen > 0)
	{
		readen = read(fd, allocated, BUFFER_SIZE);
		if (readen == 0)
			break ;
		if (readen == -1)
			return (fireforce(&stored, &allocated), NULL);
		allocated[readen] = '\0';
		stored = ft_strjoinget(stored, allocated);
		if (!stored)
			return (fireforce(&stored, &allocated), NULL);
	}
	if (ft_strcmp(stored, "") == 0)
		return (fireforce(&stored, &allocated), NULL);
	return (free(allocated), returned_line(&stored, readen));
}
