
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_cleaner
{
    struct s_cleaner *next;
    void *adress;
} t_cleaner;

t_cleaner **gethead();
void free_all_adresses();
void ft_free(void *ptr);