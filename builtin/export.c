#include "../minishell.h"

int ft_export(int argc, char **argv, t_data *data)
{
    int i;

    data->last_exit_status = 0;
    if (argc == 1)
        print_exported(data->exported);
    else
    {
        i = 1;
        while (argv[i])
        {
            if (isvalid_var(argv[i]) == false)
            {
                eputf(INVALID_IDERR, argv[i]);
                data->last_exit_status = 1;
                i++;
                continue ;
            }
            data->exported = envup(data->exported, argv[i]);
            i++;
        }
    }
    ft_freedouble(data->env);
    data->env = ft_strdup2(data->exported);
    return (data->last_exit_status);
}
