/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostr2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:35:10 by mtaleb            #+#    #+#             */
/*   Updated: 2025/02/15 18:28:24 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_lsttostr2(t_list *head)
{
	char	**ptr;
	int		lstsize;
	int		i;

	lstsize = ft_lstsize(head) + 1;
	i = 0;
	ptr = malloc(lstsize * sizeof(char *));
	while (head)
	{
		ptr[i] = ft_strdup(head->content);
		if (!ptr[i])
			return (ft_lstclear(&head), NULL);
		head = head->next;
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
