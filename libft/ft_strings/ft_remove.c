

#include "../libft.h"

void ft_remove(char ***str, int index)
{
    int i;
    int j;
    char **new;

    if(!str || !*str)
        return ;
    if (index < 0 || index >= ft_strlen2(*str))
        return ;
    new = malloc(ft_strlen2(*str) * sizeof(char *));
    if (!new)
        return ;
    i = 0;
    j = 0;
    while((*str)[i])
    {
        if (i == index)
        {
            i++;
            continue;
        }
        new[j] = ft_strdup((*str)[i]);
        if (!new[j])
        {
            ft_freedouble(&new);
            return ;
        }
        i++;
        j++;
    }
    new[j] = NULL;
    ft_freedouble(str);
    *str = new;
}
