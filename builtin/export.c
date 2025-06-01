#include "../minishell.h"

char *ascii_order(char **arr)
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

void print_variable(char *var)
{
    while (*var)
    {
        write(1, var, 1);
        if (*var == '=')
            ft_putchar('"');
        var++;
    }
    ft_putstr("\"\n");
}

void print_exported(char **exported)
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
{ // handle malloc fail and stuff like that
    char *curr;
    int i;
    int j;

    //(void) argc; (void) argv; (void) data;
    if (data->exported == NULL)
        data->exported = ft_strdup2(data->env);
    if (argc == 1)
        print_exported(data->exported);
    else
    {
        i = 1;
        while (argv[i])
        {
            j = 0;
            curr = NULL;
            while (argv[i][j])
            {
                if (ft_isalnum(argv[i][j]) || argv[i][j] == '_' || argv[i][j] == '=')
                    curr = ft_append(curr, argv[i][j], -1);
                else 
                {
                    printf("minishell: export: `%s': not a valid identifier, curr: %d\n", argv[i], argv[i][j]); // actually print to stderr
                    free(curr);
                    curr = NULL;
                    break;
                }
                j++;
            }
            if (curr != NULL)
                data->exported = ft_append2(data->exported, curr, ft_strlen2(data->exported));
            else
            {
                printf("curr is NULL\n");
            }
            i++;
        }
    }
    ft_freedouble(&data->env);
    data->env = ft_strdup2(data->exported);
    return (0);
}
