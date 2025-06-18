#include "../minishell.h"

char *ft_normalize_spaces(char *str)
{
    char *new;
    int i;
    int inword;

    new = NULL;
    i = 0;
    inword = 1;
    if (!str)
        return NULL;
    if(ft_iswhitespace(str[i]))
        i++;
    while(str[i])
    {
        if(ft_iswhitespace(str[i]) && inword)
        {
            new = ft_append(str, str[i], -1);
            i++;
            while(ft_iswhitespace(str[i]))
                i++;
        }
        else
        {
            new = ft_append(new, str[i], -1);
            inword = 1;
            i++;
        }
    }
    if (new[ft_strlen(new) - 1] == ' ')
        new[ft_strlen(new) - 1] = 0;
    free(str);
    return new;
}

int export_errors(t_data *data, char *arg, char c)
{
    if (ft_isalnum(c) || c == '_' || c == '=')
        return 0;
    else
    {
        data->last_exit_status = 1;
        eputf("minishell: export: `%s': not a valid identifier\n", arg);
        return 1;
    }
}

char *getcurrent(t_data *data, char *arg)
{
    int i;
    char *curr = NULL;
    int invarname = 1;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            invarname = 0;
        if (invarname)
        {
            if (export_errors(data, arg, arg[i]))
            {
                free(curr);
                curr = NULL;
                break ;
            }
        }
        curr = ft_append(curr, arg[i], -1);
        i++;
    }
    curr = ft_normalize_spaces(curr);
    return curr;
}

void addnewvar(t_data *data, char *newvar)
{
    int dup;

    dup = checkdups(data->exported, newvar);
    if (dup != -1)
    {
        free(data->exported[dup]);
        data->exported[dup] = ft_strdup(newvar); 
    }
    else 
        data->exported = ft_append2(data->exported, newvar, ft_strlen2(data->exported));
    if (ft_strchr(newvar, '='))
    {
        dup = checkdups(data->env, newvar);
        if (dup != -1)
        {
            free(data->env[dup]);
            data->env[dup] = ft_strdup(newvar); 
        }
        else 
            data->env = ft_append2(data->env, newvar, ft_strlen2(data->env));
    }
}

int ft_export(int argc, char **argv, t_data *data)
{
    char *curr = NULL;
    int i;

    if (data->exported == NULL)
        data->exported = ft_strdup2(data->env);
    if (argc == 1)
        print_exported(data->exported);
    else
    {
        i = 1;
        while (argv[i])
        {
            if (ft_isalpha(argv[i][0]) == 0 && argv[i][0] != '_')
            {
                eputf("minishell: export: `%s': not a valid identifier\n", argv[i]);
                data->last_exit_status = 199;
                i++;
                continue ;
            }
            curr = getcurrent(data, argv[i]);
            if (curr)
                addnewvar(data, curr);
            free(curr);
            curr = NULL;
            i++;
        }
    }
    return (0);
}
