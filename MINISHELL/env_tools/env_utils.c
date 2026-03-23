/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:37:22 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/06 23:01:24 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	vhasvalue(char *var)
{
	int		name_size;

	name_size = varname_size(var);
	if (var[name_size] == '=')
		return (1);
	return (0);
}

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
	char	**new;
	int		i;

	if (!env || !var)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (issame_var(env[i], var))
		{
			new = ft_remove2(env, i);
			ft_free(env);
			return (new);
		}
		i++;
	}
	return (env);
}

char	**envup(char **env, char *var)
{
	char	**new;
	int		i;

	if (!env || !var)
		return (NULL);
	i = 0;
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
	new = ft_append2(env, var, ft_strlen2(env));
	ft_freedouble(env);
	return (new);
}
