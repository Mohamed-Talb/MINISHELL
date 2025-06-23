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
		signals(2);
        duplication(data, command);
		if (command->flags)
		{
			if (check_builtin(command->flags[0]))
				run_builtin(data, command);
			else
			{
				check(data, command);
				execve(command->cmd, command->flags, data->env);
				if (errno == ENOENT)
					errcln(data, 127, "minishell: %s: %s\n", command->flags[0], strerror(errno));
				else if (errno == EACCES)
					errcln(data, 126, "minishell: %s: %s\n", command->flags[0], strerror(errno));
				else if(errno == ENOEXEC) // caused by test 445
					errcln(data, 126, "minishell: %s: %s\n", command->flags[0], "Permission denied");
				else
					errcln(data, 1, "minishell: %s: %s\n", command->flags[0], strerror(errno));
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
