/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 22:00:01 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/06 23:08:35 by mtaleb           ###   ########.fr       */
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
	char	*result;
	char	*varname;

	result = NULL;
	varname = NULL;
	while (*var)
	{
		varname = fappend(varname, *var);
		if (*var == '=')
		{
			result = mprintf("%s\"%s\"\n", (char *[]){varname, var + 1});
			ft_putstr(result);
			ft_free(varname);
			ft_free(result);
			return ;
		}
		var++;
	}
	varname = fappend(varname, '\n');
	ft_putstr(varname);
	ft_free(varname);
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
	int		i;
	char	*oldvar;

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
				eputf(INVALID_IDERR, (char *[]){argv[i]});
				data->exit_code = 1;
				i++;
				continue ;
			}
			oldvar = rgetenv(data->exported, argv[i]);
			if (!(oldvar && !vhasvalue(argv[i]) && vhasvalue(oldvar)))
				data->exported = envup(data->exported, argv[i]);
			i++;
		}
	}
	return (sync_envs(data), data->exit_code);
}
