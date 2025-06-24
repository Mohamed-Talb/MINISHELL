#include "../minishell.h"

char **envadd(char **env, char *newvar)
{
	char **newenv;

	newenv = NULL;
	newenv = ft_append2(newenv, newvar, ft_strlen2(env));
	if (!newenv)
		 return(eputf(MALLOC_ERROR), NULL);
	ft_freedouble(env);
	return newenv;
}

int envrm(t_data *data, char *var)
{
	int i;
	int len;
	
	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (data->env[i][len] == '=' && ft_strncmp(data->env[i], var, len) == 0)
        {
			data->env = ft_remove2(data->env, i);
			if (!data->env)
		 		return(eputf(MALLOC_ERROR), 1);
			break ;
		}
		i++;
	}
	return 0;
}

char **envup(char **env, char *newvar)
{
	int i;
	int len;
	char **newenv;

	i = 0;
	if (!newvar || !env)
		return NULL;
	while(newvar[i] && newvar[i] != '=')
		i++;
	len = i;
	while(env[i])
	{
		if (env[i][len] == '=' && ft_strncmp(env[i], newvar, len) == 0)
        {
			free(env[i]);
			env[i] = ft_strdup(newvar);
			if(!env[i])
				return(eputf(MALLOC_ERROR), NULL);
			newenv = ft_strdup2(env);
			if (!newenv)
				return(eputf(MALLOC_ERROR), NULL);
			ft_freedouble(env);
			return newenv;
		}
		i++;
	}
	newenv = envadd(env, newvar);
	return newenv;
}




int ftup_env(t_data *data, char ***env, char *newvar)
{
	int i;
    int j;

    i = 0;
	(void) data;
    while ((*env)[i])
    {
        j = 0;
        while ((*env)[i][j])
        {
            if ((*env)[i][j] == '=' && ft_strncmp((*env)[i], newvar, j) == 0)
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(newvar);
				return (0);
			}
            j++;
        }
        i++;
    }
	(*env) = ft_append2((*env), newvar, ft_strlen2((*env)));
    return (0);
}