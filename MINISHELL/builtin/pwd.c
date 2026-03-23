/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:56 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/05 12:05:49 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int argc, char **argv, t_data *data)
{
	char	*result;

	((void)argc, (void)argv, (void)data);
	result = getcwd(NULL, 0);
	if (result == NULL)
	{
		eputf("minishell: %s: %s: %s\n",
			(char *[]){GCWD_ER_P, GCWD_ER_S, strerror(errno)});
		return (1);
	}
	printf("%s\n", result);
	ft_free(result);
	return (0);
}
