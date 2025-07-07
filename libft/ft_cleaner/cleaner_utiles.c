#include "../libft.h"

typedef struct s_list
{
    struct s_lst *next;
    void *adress;
} t_list;


void *gethead()
{
    static t_list *a_adresses;
    
}

t_list *ft_lstfront(t_list **head, void *address)
{
	t_list *new_node;
	
	new_node = ft_malloc(sizeof(t_list));
	new_node->address = address;
	if(*head == NULL)
	{
		*head = new_node;
		return (*head);
	}
	new_node->next = *head;
	*head = new_node;
	return (*head);
}

t_list *ft_lstback(t_list **head, void *address)
{
	t_list *new_node;
	t_list *curr;

	new_node = ft_malloc(sizeof(t_list));
	new_node->address = address;
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
		free(temp->address);
		free(temp);
	}
	*Head = NULL;
}
