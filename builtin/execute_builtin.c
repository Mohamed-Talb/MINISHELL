#include "../minishell.h"

void execute_builtin(t_data *data, t_cmds *command)
{
	if (!ft_strcmp(command->flags[0], "echo"))
		ft_echo(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "cd"))
		ft_cd(ft_strlen2(command->flags), command->flags, data);
    else if (!ft_strcmp(command->flags[0], "pwd"))
        ft_pwd(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "export"))
        ft_export(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "unset"))
        ft_unset(ft_strlen2(command->flags), command->flags, data);
	else if (!ft_strcmp(command->flags[0], "env"))
        ft_env(ft_strlen2(command->flags), command->flags, data);
}