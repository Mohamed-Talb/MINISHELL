#include "../minishell.h"

int varname_size(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

int issame_var(char *str1, char *str2)
{
    if (varname_size(str1) == varname_size(str2) &&
        ft_strncmp(str1, str2, varname_size(str1)) == 0)     
        return (1);
    return (0);
}

int isvalid_var(char *var)
{
    int i;

    if (ft_isalpha(var[0]) == 0 && var[0] != '_')
        return (false);
    i = 1;
    while (var[i] && var[i] != '=')
    {
        if (ft_isalnum(var[i]) == false && var[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

int getenvpos(char **env, char *var)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (issame_var(env[i], var))
            return (i);
        i++;
    }
    return (-1);
}

char **envrm(char **env, char *var)
{
	int i;

    if (!env || !var)
        return (NULL);
    i = 0;
    env = ft_strdup2(env);
    while (env[i])
    {
		if (issame_var(env[i], var))
			return (ft_remove2(env, i));
        i++;
    }
	return (env);
}

char **envup(char **env, char *var)
{
	int i;

    if (!env || !var)
        return (NULL);
    i = 0;
    env = ft_strdup2(env);
    while (env[i])
    {
		if (issame_var(env[i], var))
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			return (env);
		}
        i++;
    }
	return (ft_append2(env, var, ft_strlen2(env)));
}




