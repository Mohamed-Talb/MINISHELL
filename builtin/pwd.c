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
	char	*result;

	((void)argc, (void)argv, (void)data);
	result = getcwd(NULL, 0);
	if (result == NULL)
	{
		eputf(GETCWD_ERR, strerror(errno));
		return (1);
	}
	if (ft_strcmp(ft_getenv(data->exported, "PWD"), "//") == 0)
		printf("//\n");
	else
		printf("%s\n", result);
	ft_free(result);
	return (0);
}
