/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:05:17 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 18:43:45 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	getredirections(t_data *data, t_list *list, int i)
{
	ft_lstback(&(data->cmds[i]->allred), ft_strdup(list->content));
	ft_lstlast(data->cmds[i]->allred)->type = list->type;
	return (0);
}

int	getcommand(t_cmds *command, t_list *list)
{
	char	**tmp;
	int		len;

	tmp = NULL;
	if (command->cmd == NULL)
	{
		command->flags = ft_calloc(2, sizeof(char *));
		command->flags[0] = ft_strdup(list->content);
		command->cmd = ft_strdup(list->content);
	}
	else
	{
		tmp = command->flags;
		len = ft_strlen2(command->flags);
		command->flags = ft_append2(command->flags, list->content, len);
	}
	if (tmp)
		ft_freedouble(tmp);
	return (0);
}

void	grammer(t_data *data)
{
	int		i;
	int		type;
	t_list	*list;

	i = 0;
	init_cmds(data);
	list = data->cmd_list;
	while (list)
	{
		type = list->type;
		if (type == PIPE)
			i++;
		else if (type == LEFT_HER || type == LEFT_RED || type == RIGHT_HER
			|| type == RIGHT_RED)
			getredirections(data, list, i);
		else
			getcommand(data->cmds[i], list);
		list = list->next;
	}
}
