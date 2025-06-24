#include "../libft.h"

char **ft_remove2(char **str, int index)
{
    int i;
    int j;
    char **new;

    if(!str || !*str)
        return (NULL);
    if (index < 0 || index >= ft_strlen2(str))
        return (NULL);
    new = malloc(ft_strlen2(str) * sizeof(char *));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while((*str)[i])
    {
        if (i == index)
        {
            i++;
            continue;
        }
        new[j] = ft_strdup(str[i]);
        if (!new[j])
        {
            ft_freedouble(new);
            return (NULL);
        }
        i++;
        j++;
    }
    new[j] = NULL;
    ft_freedouble(str);
    return (new);
}
