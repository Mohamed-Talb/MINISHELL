#include "../minishell.h"

int ft_env(int argc, char **argv, t_data *data)
{
    (void) argv;
    if (argc != 1)
    {
        return (1);
    }
	printdoule(data->env);
    return (0);
}
