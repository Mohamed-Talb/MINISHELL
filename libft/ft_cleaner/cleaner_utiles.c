#include "cleaner.h"

t_cleaner **gethead()
{
    static t_cleaner *head = NULL;
    return &head;
}

void free_all_adresses()
{
    t_cleaner **head;
    t_cleaner *curr;
    t_cleaner *tmp;

    head = gethead();
    curr = *head;
    while(curr)
    {
        tmp = curr;
        curr = curr->next;
        free(tmp->adress);
        free(tmp);
    }
    *head = NULL;
}

void ft_free(void *ptr)
{
    t_cleaner **head;
    t_cleaner *curr;
    t_cleaner *prev;

    head = gethead();
    curr = *head;
    prev = NULL;
    if (curr->adress == ptr)
    {
        if (prev)
            prev->next = curr->next;
        else
            *head = curr->next;
        free(curr->adress);
        free(curr); 
        return;
    }
    prev = curr;
    curr = curr->next;
}

