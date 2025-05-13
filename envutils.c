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
			ft_remove(&env, i);
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
			ft_remove(&env, i);
			break ;
		}
		i++;
	}
	newenv = ft_append2(env, newvar, i+1);
	return newenv;
}

// int main(int ac, char **av, char **env)
// {
// 	char **myenv;
// 	myenv = ft_strdup2(env);
// 	(void)ac;
// 	(void)av;

// 	int i = 0;
// 	char *var = "mtaleb=0";
// 	myenv = addvar(myenv, var);
// 	while (myenv[i])
// 	{
// 		printf("%s\n", myenv[i]);
// 		i++;
// 	}
// 	printf("\n\n\n\n\n");
// 	i = 0;
// 	char *newvar="mtaleb=1";
// 	myenv = upvar(myenv, newvar);
// 	while (myenv[i])
// 	{
// 		printf("%s\n", myenv[i]);
// 		i++;
// 	}
// }