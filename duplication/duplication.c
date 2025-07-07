#include "../minishell.h"

void files_manager(t_data *data, t_cmds *cmd, t_list *input, t_list *output)
{
	t_list *curr;
    int fd;

	curr = cmd->allred;
	while (curr)
	{
		fd = openredfiles(data, curr);
        if (curr == input)
            cmd->infd = fd;
        else if (curr == output)
            cmd->outfd = fd;
        else 
            close(fd);
		curr = curr->next;
	}
}

void last_in_out(t_cmds *cmd, t_list **input, t_list **output)
{
    t_list *list = cmd->allred;
    while (list)
    {
        if (list->type == LEFT_HER || list->type == LEFT_RED)
            *input = list;
        if (list->type == RIGHT_RED || list->type == RIGHT_HER)
            *output = list;
        list = list->next;
    }
}

int duplication(t_data *data, t_cmds *cmd)
{
    t_list *input = NULL;
    t_list *output = NULL;

    last_in_out(cmd, &input, &output);
    files_manager(data, cmd, input, output);
    if (cmd->infd != -1)
    {
        dup2(cmd->infd, 0);
        close(cmd->infd);
    }
    else if (cmd->infd == -1 && cmd->pipein != -1)
          dup2(cmd->pipein, 0);
    if (cmd->outfd != -1)
    {
        dup2(cmd->outfd, 1);
        close(cmd->outfd);
    }
    else if (cmd->outfd == -1 && cmd->pipeout != -1)
          dup2(cmd->pipeout, 1);
    return (0);
}
