/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:02:35 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 22:02:39 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char **env, char *var)
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
			if (env[i][j] == '=' && issame_var(env[i], var))
				return (&env[i][j + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}
