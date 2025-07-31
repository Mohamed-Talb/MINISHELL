/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:52 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/31 18:26:44 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isvalid_var(char *var)
{
	int	i;

	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (false);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == false && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static char	*ascii_order(char **arr)
{
	int		i;
	char	*prev;

	i = 0;
	prev = arr[0];
	while (arr[i] != NULL)
	{
		if (ft_strcmp(prev, arr[i]) < 0)
			prev = arr[i];
		i++;
	}
	return (prev);
}

static void	print_variable(char *var)
{
	int name_size;
	char *str;
	char *key;

	name_size = varname_size(var);
	key = ft_substr(var, 0, name_size + 1);
	str = mprintf("%s\"%s\"\n", key, &var[name_size + 1]);
	ft_putstr(str);
	ft_free(key);
	ft_free(str);
}

static void	print_exported(char **exported)
{
	char	*prev;
	char	*curr;
	int		i;
	int		j;

	j = ft_strlen2(exported);
	prev = NULL;
	while (j > 0)
	{
		i = 0;
		curr = ascii_order(exported);
		while (exported[i])
		{
			if (ft_strcmp(curr, exported[i]) > 0 && (prev == NULL
					|| ft_strcmp(prev, exported[i]) < 0))
				curr = exported[i];
			i++;
		}
		prev = curr;
		print_variable(prev);
		j--;
	}
}

int	ft_export(int argc, char **argv, t_data *data)
{
	int	i;

	data->exit_code = 0;
	if (argc == 1)
		print_exported(data->exported);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (isvalid_var(argv[i]) == false)
			{
				eputf(INVALID_IDERR, argv[i]);
				data->exit_code = 1;
				i++;
				continue ;
			}
			data->exported = envup(data->exported, argv[i]);
			i++;
		}
	}
	sync_envs(data);
	return (data->exit_code);
}
