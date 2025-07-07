#include "../minishell.h"

void *ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
		ft_putstr_fd("memory allocation faild", 2);
        free_all_addresses();
        exit(1);
    }
    t_list **head = get_head();
    if (!ft_lstback(head, ptr))
    {
		ft_putstr_fd("memory allocation faild", 2);
        free(ptr);
        free_all_addresses();
        exit(1);
    }
    return ptr;
}
