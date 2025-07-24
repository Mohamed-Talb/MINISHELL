/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:34:56 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/24 16:10:32 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int argc, char **argv, t_data *data)
{
	char	cwd[999999];
	char	*result;

	((void)argc, (void)argv, (void)data);
	result = getcwd(cwd, sizeof(cwd));
	if (result == NULL)
	{
		eputf(GETCWD_ERR, strerror(errno));
		return (1);
	}
	printf("%s\n", result);
	return (0);
}
