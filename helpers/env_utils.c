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

/*  This Function is dangerous if you will not be setting the return back to env
    This happens if we change in only one variable of the list, also happens with envrm  */
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

char *ft_getenv(char **env, const char *var)
{
    int i;
    int j;
    
    if (!env || !var)
        return (NULL);
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

char **adjust_shell_level(char **env, int change) // this function is a 90% copy of bash, might this be called cheating?
{
    char *new_level;
    char *old_SHLVL;
    int shell_level;
    long old_level;

    old_SHLVL = ft_getenv(env, "SHLVL");
    if (old_SHLVL == NULL || old_SHLVL[0] == '\0' || !atoi_sign(old_SHLVL))
        old_level = 0;
    else
        old_level = ft_atoi(old_SHLVL);
    shell_level = old_level + change;
    if (shell_level < 0)
        shell_level = 0;
    else if (shell_level >= 1000)
    {
        eputf("minishell: warning: shell level (%i) too high, resetting to 1\n", shell_level);
        shell_level = 1;
    }
    new_level = ft_itoa(shell_level);
    new_level = ft_strjoin_fc("SHLVL=", new_level, 2);
    return (envup(env, new_level));
}
