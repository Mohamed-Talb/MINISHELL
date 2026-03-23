/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:40 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/02 19:19:00 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// echo -

int	ft_echo(int argc, char **argv, t_data *data)
{
	int	rm_newline;
	int	i;

	i = 1;
	(void)data;
	rm_newline = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-' || argv[i][1] == '\0'
			|| !respects_set(&argv[i][1], "n"))
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
