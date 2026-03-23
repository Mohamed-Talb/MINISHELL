/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:30:06 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/02 12:09:12 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*creat_node(t_data *data)
{
	char	*str;
	t_list	*new;

	str = ft_strdup("");
	new = ft_lstback(&data->cmd_list, str);
	return (new);
}

void	set_errors(t_data *data, char *error, int exitcode)
{
	ft_lstlast(data->cmd_list)->error = error;
	data->exit_code = exitcode;
}

int	isdirectory(char *path)
{
	struct stat	sb;

	return ((stat(path, &sb) == 0) && S_ISDIR(sb.st_mode));
}

void	errors(char *error, int exitcode)
{
	ft_putstr_fd(error, 2);
	free_all_adresses();
	exit(exitcode);
}
