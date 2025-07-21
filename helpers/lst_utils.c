#include "../minishell.h"

t_list *ft_lstnew(void *content)
{
	t_list *new_node;
	
	new_node = ft_calloc(1, sizeof(t_list));
	new_node->content = content;
	return (new_node);
}

t_list *ft_lstfront(t_list **head, void *content)
{
	t_list *new_node;
	
	new_node = ft_lstnew(content);
	if (*head == NULL)
	{
		*head = new_node;
		return (*head);
	}
	new_node->next = *head;
	*head = new_node;
	return (*head);
}

t_list *ft_lstback(t_list **head, void *content)
{
	t_list *new_node;
	t_list *curr;

	new_node = ft_lstnew(content);
	if((*head) == NULL) 
	{
		*head = new_node;
		return (new_node);
	}
	curr = *head;
	while(curr->next != NULL) 
	{
		curr = curr->next;
	}
	curr->next = new_node;
	return (new_node);
}

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
		ft_free(temp->content);
		ft_free(temp);
	}
	*Head = NULL;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (!lst)
		return (NULL);
	curr = lst;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

t_list	*ft_lstprevlast(t_list *lst)
{
	t_list	*curr;

	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	curr = lst;
	while (curr->next->next != NULL)
	{
		curr = curr->next;
	}
	return (curr);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
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

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	t_list *curr = lst;
	while (curr != NULL)
	{
		f(curr->content);
		curr = curr->next;
	}
}