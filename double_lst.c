#include "minishell.h"

t_dlist *ft_dlstfront(t_dlist **head, void *content)
{
	t_dlist *new_node;
	
	new_node = malloc(sizeof(t_dlist));
	new_node->content = content;
	new_node->prev = NULL;
	new_node->next = NULL;
	if(*head == NULL)
	{
		*head = new_node;
		return (*head);
	}
	new_node->next = *head;
	(*head)->prev = new_node;
	*head = new_node;
	return (*head);
}

t_dlist *ft_dlstback(t_dlist **head, void *content)
{
	t_dlist *new_node;
	t_dlist *curr;

	new_node = malloc (sizeof(t_dlist)); 
	if (! new_node)
	{
		return NULL;
	}
	new_node->prev = NULL;
	new_node->content = content;
	new_node->next = NULL;
	if((*head) == NULL) 
	{
		*head = new_node;
		return (*head);
	}
	curr = *head;
	while(curr->next != NULL) 
	{
		curr = curr->next;
	}
	curr->next = new_node;
	new_node->prev = curr; 
	return (*head);
}

void	ft_dlstclear(t_dlist **Head)
{
	t_dlist	*curr;
	t_dlist	*temp;

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

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	t_dlist	*curr;

	if (!lst)
		return (NULL);
	curr = lst;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

int	ft_dlstsize(t_dlist *lst)
{
	t_dlist	*curr;
	int		i;

	curr = lst;
	i = 0;
	if (lst == 0)
		return (0);
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

void f(void *content)
{
	char *str;

	str = (char *) content;
	printf("str is: %s\n", str);
}

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}