#include "../libft.h"

char **ft_remove2(char **str, int index)
{
    int len;
    int i;
    int j;
    char **new;

    if (!str || !*str)
        return (NULL);
    len = ft_strlen2(str);
    if (index < 0 || index >= len)
        return (NULL);
    new = (char **) ft_calloc(len, sizeof(char *));
    i = 0;
    j = 0;
    while (str[i])
    {
        if (i == index)
        {
            free(str[i]);
            i++;
            continue;
        }
        else
            new[j] = str[i];
        i++;
        j++;
    }
    free(str);
    return (new);
}
