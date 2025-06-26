#include "../minishell.h"

static char *getcmdname(char *cmd)
{
	int i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		while(cmd[i])
			i++;
		while(cmd[i - 1] != '/')
			i--;
		return (&cmd[i]);
	}
	else
		return cmd; 
}

int check_builtin(char *cmd)
{
	char *cmdname;

	cmdname = getcmdname(cmd);
	if (!ft_strcmp(cmdname, "echo") || !ft_strcmp(cmdname, "cd")
		|| !ft_strcmp(cmdname, "pwd") || !ft_strcmp(cmdname, "export")
		|| !ft_strcmp(cmdname, "unset") || !ft_strcmp(cmdname, "env")
		|| !ft_strcmp(cmdname, "exit"))
		return (1);
	return (0);
}

void execute_builtin(t_data *data, t_cmds *command)
{
	int exst;
	int stdin_dup;
	int stdout_dup;

	exst = 0;
	char *cmdname;
	stdin_dup = dup(0);
	stdout_dup = dup(1);  //  why that two dup; ??????????????????????????????
	duplication(data, data->cmds[0]);
	cmdname = getcmdname(command->flags[0]);
	if (!ft_strcmp(cmdname, "echo"))
		exst = ft_echo(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "cd"))
		exst = ft_cd(ft_strlen2(command->flags), command->flags, data);
    else if (!ft_strcmp(cmdname, "pwd"))
        exst = ft_pwd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "export"))
        exst = ft_export(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "unset"))
        exst = ft_unset(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "env"))
        exst = ft_env(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(cmdname, "exit"))
	{
        exst = ft_exit(ft_strlen2(command->flags), command->flags, data);
		if (exst == -1)
			exst = 1;
		else
			(free_data(data), exit(exst));
	}
	data->last_exit_status = exst;
	dup2(stdin_dup, 0);
	dup2(stdout_dup, 1);
}
