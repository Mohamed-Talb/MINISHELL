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

int issame_var(char *str1, char *str2)
{
    int pos1;
    int pos2;

    pos1 = posin_set(str1, '=');
    pos2 = posin_set(str2, '=');
    if (pos1 < pos2)
        return (!ft_strncmp(str1, str2, pos1));
    return (!ft_strncmp(str1, str2, pos2));
}

int no_dups(t_data *data, char *target)
{
    int i;
    
    for (i = 0; data->exported[i]; i++)
    {
        if (issame_var(data->exported[i], target))
            return (i);
    }
    return (-1);
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
                    eputf("minishell: export: `%s': not a valid identifier\n", argv[i]); // actually print to stderr
                    free(curr);
                    curr = NULL;
                    break;
                }
                j++;
            }
            j = no_dups(data, argv[i]);
            if (j != -1 && curr != NULL)
            {
                free(data->exported[j]);
                data->exported[j] = ft_strdup(curr);
            }
            else if (curr != NULL)
                data->exported = ft_append2(data->exported, curr, ft_strlen2(data->exported));
            else
            {
                printf("curr is NULL\n");
            }
            i++;
        }
    }
    ft_freedouble(&data->env);
    data->env = ft_strdup2(data->exported); //dont add the ones without '='
    return (0);
}
