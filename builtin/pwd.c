#include "../minishell.h"

int ft_pwd(int argc, char **argv, t_data *data) // PWD should be updated in envp too, add that in cd
{
    char cwd[2000];

    (void) argc;
    (void) argv;
    (void) data;
    ft_putstr(getcwd(cwd, sizeof(cwd))); 
    ft_putstr("\n");
    return (0);
}
