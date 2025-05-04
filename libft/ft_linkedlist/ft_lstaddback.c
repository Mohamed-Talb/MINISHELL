/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:52:06 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:27:22 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstaddback(t_list **Head, void *content)
{
	t_list	*new_node;
	t_list	*curr;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	if (!*Head)
	{
		*Head = new_node;
		return (*Head);
	}
	curr = *Head;
	while (curr->next)
	{
		curr = curr->next;
	}
	curr->next = new_node;
	return (new_node);
}
