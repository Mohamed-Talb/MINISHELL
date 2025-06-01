#include "../minishell.h"

int ft_env(int argc, char **argv, t_data *data)
{
    (void) argc;
    (void) argv;
	printdoule(data->env);
    return (0);
}