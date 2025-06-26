#include "../minishell.h"

int ft_pwd(int argc, char **argv, t_data *data)
{
    char cwd[999999];
    char *result;

    ((void) argc, (void) argv, (void) data);
    result = getcwd(cwd, sizeof(cwd));
    if (result == NULL)
    {
        eputf("pwd: %s: %s\n", GETCWD_ERR, strerror(errno));
        return (1);
    }
    ft_printf("%s\n", result);
    return (0);
}
