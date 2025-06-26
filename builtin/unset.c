#include "../minishell.h"

/*
    1- SHLVL is lowel by 1 in env than exported
    2- expand uses exported not env
*/

int ft_unset(int argc, char **argv, t_data *data)
{
    int i;

    i = 1;
    while (i < argc)
    {
        data->exported = envrm(data->exported, argv[i]);
        i++;
    }
    ft_freedouble(data->env);
    data->env = ft_strdup2(data->exported);
    return (0);
}
