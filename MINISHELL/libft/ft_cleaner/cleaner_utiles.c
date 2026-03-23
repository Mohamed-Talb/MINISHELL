/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:40:13 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/03 21:51:42 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_cleaner	**gethead(void)
{
	static t_cleaner	*head = NULL;

	return (&head);
}

void	free_all_adresses(void)
{
	t_cleaner	**head;
	t_cleaner	*curr;
	t_cleaner	*tmp;

	head = gethead();
	curr = *head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->adress);
		free(tmp);
	}
	*head = NULL;
}

void	ft_free(void *ptr)
{
	t_cleaner	**head;
	t_cleaner	*curr;
	t_cleaner	*prev;

	if (ptr == NULL)
		return ;
	head = gethead();
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->adress == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->adress);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	free(ptr);
}
