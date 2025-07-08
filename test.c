#include "libft/libft.h"
#include <stdio.h>

int main()
{
    char *str = ft_malloc(6);
    ft_memset(str, 0, 6);
    ft_strlcpy(str, "hello", 6);
    printf("str is: %s\n", str);
    free_all_adresses();
}