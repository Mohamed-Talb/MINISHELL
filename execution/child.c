#include "../minishell.h"

int	child(t_data *data, t_cmds *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		struct sigaction sa;
		signals(&sa, 2);
		check(data, command);
        duplication(data, command);
        execve(command->cmd, command->flags, data->env);
        errors(data, "execve failed\n", 126);
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