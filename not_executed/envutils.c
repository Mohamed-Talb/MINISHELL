#include "minishell.h"

char **addvar(char **env, char *var)
{
	char **newenv;
	newenv = ft_append2(env, var, ft_strlen2(env));
	return newenv;
}

char **rmvar(char **env, char *var)
{
	char **newenv ;
	int i;
	
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
		{
			ft_remove2(&env, i);
			break ;
		}
		i++;
	}
	newenv = ft_strdup2(env);
	ft_freedouble(&env);
	return (newenv);
}

char **upvar(char **env, char *newvar)
{
	int i;
	int namelen;
	char **newenv;

	i = 0;
	while (newvar[i] != '=')
		i++;
	namelen = i;
	i = 0;
	while(env[i])
	{
		if(!ft_strncmp(env[i], newvar, namelen))
		{
			ft_remove2(&env, i);
			break ;
		}
		i++;
	}
	newenv = ft_append2(env, newvar, i+1);
	return newenv;
}
