/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:37:28 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 13:38:19 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char **env, const char *var)
{
	int	i;
	int	j;

	if (!env || !var)
		return (NULL);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=' && ft_strncmp(env[i], var, j) == 0)
				return (&env[i][j + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}
