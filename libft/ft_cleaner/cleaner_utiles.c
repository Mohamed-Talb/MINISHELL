#include "cleaner.h"

static t_list **get_head(void)
{
    static t_list *head = NULL;
    return &head;
}

static t_list *ft_lstback(t_list **head, void *address)
{
    t_list *new_node = malloc(sizeof(t_list)); 
    new_node->address = address;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        t_list *curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new_node;
    }
    return new_node;
}

void ft_add_address(void *ptr)
{
    t_list **head = get_head();
    ft_lstback(head, ptr);
}

void free_all_addresses()
{
    t_list **head = get_head();
    t_list *curr = *head;
    t_list *temp;

    while (curr)
    {
        temp = curr;
        curr = curr->next;
        free(temp->address); 
        free(temp);      
    }
    *head = NULL;
}

