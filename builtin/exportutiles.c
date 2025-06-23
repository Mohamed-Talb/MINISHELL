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
    int len1 = posin_set(str1, '=');
    int len2 = posin_set(str2, '=');

    if (len1 != len2)
        return 0;
    return (ft_strncmp(str1, str2, len1) == 0);
}

int checkdups(char **variables, char *target)
{
    int i;
    
    for (i = 0; variables[i]; i++)
    {
        if (issame_var(variables[i], target))
            return (i);
    }
    return (-1);
}

char *getownenv(char **env, char *var)
{
    int i;
    int j;

    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j])
        {
            if (env[i][j] == '=' && ft_strncmp(env[i], var, j) == 0)
                return (&env[i][j + 1]);
            j++;
        }
        i++;
    }
    return (NULL);
}

int getenvpos(char **env, char *var)
{
    int i;
    int j;

    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j])
        {
            if (env[i][j] == '=' && ft_strncmp(env[i], var, j) == 0)
                return (i);
            j++;
        }
        i++;
    }
    return (-1);
}
