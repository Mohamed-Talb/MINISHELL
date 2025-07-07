
# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_list
{
    struct s_list *next;
    void *address;
} t_list;