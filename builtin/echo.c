/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:40 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/19 10:34:41 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	respects_set(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in_set(set, str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(int argc, char **argv, t_data *data)
{
	int	rm_newline;
	int	i;

	i = 1;
	(void)data;
	rm_newline = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-' || !respects_set(&argv[i][1], "n"))
			break ;
		rm_newline = 1;
		i++;
	}
	while (i < argc - 1)
	{
		ft_putstr(argv[i]);
		ft_putchar(' ');
		i++;
	}
	if (argv[i] != NULL)
		ft_putstr(argv[i]);
	if (rm_newline != 1)
		ft_putchar('\n');
	return (0);
}
