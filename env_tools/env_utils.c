/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:37:22 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/23 22:27:22 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	varname_size(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

int	issame_var(char *str1, char *str2)
{
	if (varname_size(str1) == varname_size(str2) && ft_strncmp(str1, str2,
			varname_size(str1)) == 0)
		return (1);
	return (0);
}

char	**envrm(char **env, char *var)
{
	int	i;

	if (!env || !var)
		return (NULL);
	i = 0;
	env = ft_strdup2(env);
	while (env[i])
	{
		if (issame_var(env[i], var))
			return (ft_remove2(env, i));
		i++;
	}
	return (env);
}

char	**envup(char **env, char *var, int choise)
{
	int	i;

	if (!env || !var)
		return (NULL);
	i = 0;
	env = ft_strdup2(env);
	while (env[i])
	{
		if (issame_var(env[i], var))
		{
			ft_free(env[i]);
			env[i] = ft_strdup(var);
			return (env);
		}
		i++;
	}
	if (choise == 1)
		return (ft_append2(env, var, ft_strlen2(env)));
}
