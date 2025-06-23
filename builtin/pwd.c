#include "../minishell.h"

int ft_pwd(int argc, char **argv, t_data *data) // PWD should be updated in envp too, add that in cd
{
    char cwd[2000];
    char *result;

    (void) argc;
    (void) argv;
    (void) data;
    result = getcwd(cwd, sizeof(cwd));
    if (result == NULL)
    {
        eputf("pwd: %s: %s\n", GETCWD_ERR, strerror(errno));
        return (0);
    }
    ft_putstr(result);
    ft_putstr("\n");
    return (0);
}
