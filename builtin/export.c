#include "../minishell.h"

static char *ascii_order(char **arr)
{
    int i;
    char *prev;

    i = 0;
    prev = arr[0];
    while (arr[i] != NULL)
    {
        if (ft_strcmp(prev, arr[i]) < 0)
            prev = arr[i];
        i++;
    }
    return (prev);
}

static void print_variable(char *var)
{
    while (*var)
    {
        ft_putchar(*var);
        if (*var == '=')
        {
            ft_printf("\"%s\"\n", var + 1);
            return ;
        }
        var++;
    }
    ft_putchar('\n');
}

static void print_exported(char **exported)
{
    char *prev;
    char *curr;
    int i;
    int j;

    j = ft_strlen2(exported);
    prev = NULL;
    while (j > 0)
    {
        i = 0;
        curr = ascii_order(exported);
        while (exported[i])
        {
            if (ft_strcmp(curr, exported[i]) > 0 && (prev == NULL || ft_strcmp(prev, exported[i]) < 0))
                curr = exported[i];
            i++;
        }
        prev = curr;
        print_variable(prev);
        j--;
    }
}

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
    sync_envs(data);
    return (data->last_exit_status);
}
