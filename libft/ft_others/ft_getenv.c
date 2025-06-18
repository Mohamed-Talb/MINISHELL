#include "../libft.h"

char *ft_getenv(char **env, const char *varname)
{
    size_t len;
    int i = 0;

    if (!env || !varname)
        return NULL;

    len = ft_strlen(varname);
    while (env[i])
    {
        if (ft_strncmp(env[i], varname, len) == 0 && env[i][len] == '=')
            return ft_strdup(env[i] + len + 1); 
        i++;
    }
    return NULL;
}
