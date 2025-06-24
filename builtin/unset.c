#include "../minishell.h"

char **remove2_plus(char **str, int index)
{
    int len;
    int i;
    int j;
    char **new;

    if (!str || !*str)
        return (NULL);
    len = ft_strlen2(str);
    if (index < 0 || index >= len)
        return (NULL);
    new = (char **) ft_calloc(len, sizeof(char *));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (i == index)
        {
            free(str[i]);
            i++;
            continue;
        }
        else
            new[j] = str[i];
        i++;
        j++;
    }
    return (new);
}

int get_path(char **envp, char *target)
{
	int	i;
    int len;

	i = 0;
    len = ft_strlen(target);
	while (envp[i])
	{
		if (!ft_strncmp(target, envp[i], len) && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int isvalid_var(char *var)
{
    int i;

    if (ft_isalpha(var[0]) == 0 && var[0] != '_')
        return (0);
    i = 1;
    while (var[i] && var[i] != '=')
    {
        if (ft_isalnum(var[i]) == false && var[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int ft_unset(int argc, char **argv, t_data *data)
{
    int i;
    int temp;

    i = 1;
    while (i < argc)
    {
        temp = get_path(data->exported, argv[i]);
        if (temp != -1)
            data->exported = remove2_plus(data->exported, temp);
        i++;
    }
    ft_freedouble(data->env);
    data->env = ft_strdup2(data->exported);
    return (0);
}
