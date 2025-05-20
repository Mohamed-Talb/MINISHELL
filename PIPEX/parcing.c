
#include "pipex.h"

static char	*getcommand(char *av)
{
	char	**ptr;
	char	*cmd;

	ptr = NULL;
	ptr = getargs(av);
	if (!ptr || !ptr[0])
		return (NULL);
	cmd = ft_strdup(ptr[0]);
	if (!cmd)
	{
		if (ptr)
			ft_freedouble(&ptr);
		return (NULL);
	}
	return (ft_freedouble(&ptr), cmd);
}

static char	**getflags(char *av)
{
	int		i;
	char	**ptr;
	char	**flags;

	i = 0;
	ptr = getargs(av);
	if (!ptr || !ptr[0])
		return (NULL);
	i = ft_strlen2(ptr);
	flags = ft_strdup2(ptr);
	ft_freedouble(&ptr);
	return (flags);
}

static void	getpaths(char **envp, t_info *info)
{
	int	i;

	i = 0;
	info->paths = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			info->paths = ft_split(&envp[i][5], ':');
			break ;
		}
		i++;
	}
	if (!info->paths)
		displayerrors(info, "command not found\n", 1);
}

void	getinfo(t_info *info, char *av, char **env)
{
	if (av[0] == '\0')
		displayerrors(info, "invalide input\n", 1);
	if (info->cmd)
		free(info->cmd);
	if (info->paths)
		ft_freedouble(&info->paths);
	if (info->flags)
		ft_freedouble(&info->flags);
	info->cmd = NULL;
	getpaths(env, info);
	info->cmd = getcommand(av);
	info->flags = getflags(av);
	if (!info->cmd || !info->flags)
		displayerrors(info, "Error\n", 1);
}
