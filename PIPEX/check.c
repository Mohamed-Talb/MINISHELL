
#include "pipex.h"

static void	printerrors(t_info *info)
{
	if (!info->found)
		displayerrors(info, "command not found\n", 127);
	if (!info->permission)
		displayerrors(info, "permission denied\n", 126);
}

static void	helper(t_info *info)
{
	ft_freedouble(&info->paths);
	info->paths = malloc(2 * sizeof(char *));
	if (!info->paths)
		displayerrors(info, "memory allocation failed\n", 1);
	info->paths[0] = ft_strdup(info->cmd);
	info->paths[1] = NULL;
	return ;
}

static void	getabspaths(t_info *info, int i)
{
	char	*tmp;

	if (ft_strchr(info->cmd, '/'))
	{
		helper(info);
		return ;
	}
	while (info->paths[i])
	{
		tmp = info->paths[i];
		info->paths[i] = ft_strjoin(info->paths[i], "/");
		if (!info->paths[i])
			displayerrors(info, "memory allocation failed\n", 1);
		free(tmp);
		tmp = info->paths[i];
		info->paths[i] = ft_strjoin(info->paths[i], info->cmd);
		if (!info->paths[i])
			displayerrors(info, "memory allocation failed\n", 1);
		free(tmp);
		i++;
	}
	return ;
}

void	check(t_info *info, int i)
{
	(1) && (info->permission = false, info->found = false);
	getabspaths(info, 0);
	if (!info->paths || !info->paths[0])
		displayerrors(info, "memory allocation faild\n", 1);
	while (info->paths[i])
	{
		if (access(info->paths[i], F_OK) == 0)
		{
			info->found = true;
			if (access(info->paths[i], X_OK) == 0)
			{
				info->permission = true;
				if (info->cmd)
					free(info->cmd);
				info->cmd = ft_strdup(info->paths[i]);
				if (!info->cmd)
					displayerrors(info, "memory allocation faild\n", 1);
				break ;
			}
		}
		i++;
	}
	if (!info->found || !info->permission)
		printerrors(info);
}
