#include "../minishell.h"

int	child(t_data *data, t_cmds *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		check(data, command);
        duplication(data, command);
        // execve(command->cmd[0], &command->cmd[1], data->env);
        execve(command->cmd[0], command->cmd, data->env);
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