#include "../minishell.h"

int check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void execute_builtin(t_data *data, t_cmds *command)
{
	int exst = 0;
	
	printf("inside builtins\n");
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
		ft_putstr("exit\n");
		free_data(data);
		exit(exst);
	}
	data->last_exit_status = exst;
}
