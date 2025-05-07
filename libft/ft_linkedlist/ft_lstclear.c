/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:52:17 by mtaleb            #+#    #+#             */
/*   Updated: 2025/05/07 09:31:48 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **Head)
{
	t_list	*curr;
	t_list	*temp;

	curr = *Head;
	if (*Head == NULL)
		return ;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->content);
		free(temp);
	}
	*Head = NULL;
}
