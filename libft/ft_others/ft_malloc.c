#include "../libft.h"

static t_cleaner *ft_lstback(t_cleaner **head, void *adress)
{
    t_cleaner *new = malloc(sizeof(t_cleaner));
    if (!new)
        return NULL;
    new->adress = adress;
    new->next = NULL;
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        t_cleaner *curr = *head;
        while(curr->next)
            curr = curr->next;
        curr->next = new;
    }
    return new;
}

void *ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
		ft_putstr_fd("memory allocation faild", 2);
        free_all_adresses();
        exit(1);
    }
    t_cleaner **head = gethead();
    if (!ft_lstback(head, ptr))
    {
		ft_putstr_fd("memory allocation faild", 2);
        free(ptr);
        free_all_adresses();
        exit(1);
    }
    return ptr;
}
