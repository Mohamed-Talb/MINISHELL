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
    sync_envs(data);
    return (0);
}
