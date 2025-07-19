#include "../minishell.h"

void run_builtin(t_data *data, t_cmds *command)
{
	int exst;

	exst = 0;
	if (!ft_strcmp(command->flags[0], "echo"))
		exst = ft_echo(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "cd"))
		exst = ft_cd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "pwd"))
        exst = ft_pwd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "export"))
        exst = ft_export(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "unset"))
        exst = ft_unset(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "env"))
        exst = ft_env(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "exit"))
	{
        exst = ft_exit(ft_strlen2(command->flags), command->flags, data);
		if (exst == -1)
			exst = 1;
	}
	exit(exst);
}

int	child(t_data *data, t_cmds *command)
{
	int	pid;

	signal_state(2);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
				// else if(errno == ENOEXEC) // caused by test 445
				// 	errcln(data, 126, "minishell: %s: %s\n", command->flags[0], "Permission denied");
				else
					errcln(data, 1, "minishell: %s: %s\n", command->flags[0], strerror(errno));
			}
		}
		else
			exit(0);
	}
	else if (pid > 0)
	{
		signal_state(0);
		close(command->pipein);
		close(command->pipeout);
	}
	else
		errors(data, "Unable to create a new process\n", 1);
	return (pid);
}
