#include "../libft.h"

void *ft_malloc(size_t size)
{
    char *ptr;

    ptr = malloc(size);
    if (ptr == NULL)
    {
        ft_putstr_fd("memory allocation faild\n", 2);
        exit(1);
    }
    return (ptr);
}
