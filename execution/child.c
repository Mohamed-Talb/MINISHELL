#include "../minishell.h"

void run_builtin(t_data *data, t_cmds *command)
{
	duplication(data, command);
	if (!ft_strcmp(command->flags[0], "echo"))
		exit(ft_echo(ft_strlen2(command->flags), command->flags, data));
	else if (!ft_strcmp(command->flags[0], "cd"))
		exit(ft_cd(ft_strlen2(command->flags), command->flags, data));
	else if (!ft_strcmp(command->flags[0], "pwd"))
        exit(ft_pwd(ft_strlen2(command->flags), command->flags, data));
	else if (!ft_strcmp(command->flags[0], "export"))
        exit(ft_export(ft_strlen2(command->flags), command->flags, data));
	else if (!ft_strcmp(command->flags[0], "unset"))
        exit(ft_unset(ft_strlen2(command->flags), command->flags, data));
	else if (!ft_strcmp(command->flags[0], "env"))
        exit(ft_env(ft_strlen2(command->flags), command->flags, data));
}

int	child(t_data *data, t_cmds *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		struct sigaction sa;
		signals(&sa, 2);
        duplication(data, command);
		if (command->flags)
		{
			if (check_builtin(command->flags[0]))
				run_builtin(data, command);
			else
			{
				if (ft_strcmp(command->flags[0], ":") == 0
					|| ft_strcmp(command->flags[0], "!") == 0)
					exit(0);
				check(data, command);
				execve(command->cmd, command->flags, data->env);
				errors(data, "execve failed\n", 126);
			}
		}
		else
			exit(0);
	}
	else if (pid > 0)
	{
		close(command->pipein);
		close(command->pipeout);
	}
	else
		errors(data, "Unable to create a new process\n", 1);
	return (pid);
}
