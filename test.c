#include "libft/libft.h"
#include <stdio.h>

// int main()
// {
//     char *str = ft_malloc(6);
//     ft_memset(str, 0, 6);
//     ft_strlcpy(str, "hello", 6);
//     printf("str is: %s\n", str);
//     free_all_adresses();
// }

int main()
{
    // int i;
    // char arr[] = "hello";
    // i = 0;
    // while (true)
    // {
    //     putchar(arr[i]);
    //     i++;
    // }
    int (*p)[5][9];
	int *p1[5][9];
    printf("%d\n", sizeof(*p));
    printf("%d\n", sizeof(p1));
}