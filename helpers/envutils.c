#include "../minishell.h"

// char **addvar(char **env, char *var)
// {
// 	char **newenv;
// 	newenv = ft_append2(env, var, ft_strlen2(env));
// 	return newenv;
// }

// char **rmvar(char **env, char *var)
// {
// 	char **newenv ;
// 	int i;
	
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], var, ft_strlen(var)))
// 		{
// 			ft_remove2(&env, i);
// 			break ;
// 		}
// 		i++;
// 	}
// 	newenv = ft_strdup2(env);
// 	ft_freedouble(&env);
// 	return (newenv);
// }

int upenv(t_data *data, char *newvar)
{
	int i;
	int namelen;
	char **newenv;

	i = 0;
	while(newvar[i] != '=')
		i++;
	namelen = i;
	while(data->env[i])
	{
		if (ft_strncmp(data->env[i], newvar, namelen) == 0 && data->env[i][namelen] == '=')
        {
			free(data->env[i]);
			data->env[i] = ft_strdup(newvar);
			if (data->env[i] == NULL)
				return (ft_putstr_fd(MALLOC_ERROR, 2), 1);
			return 0;
		} 
		i++;
	}
	newenv = ft_append2(data->env, newvar, ft_strlen2(data->env));
	if (newenv == NULL)
		return (ft_putstr_fd(MALLOC_ERROR, 2), 1);
	ft_freedouble(&data->env);
	data->env = newenv;
	return 0;
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
