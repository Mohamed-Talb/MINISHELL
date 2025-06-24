#include "../minishell.h"

void files_manager(t_data *data, t_cmds *cmd)
{
	t_list *curr;

	curr = cmd->allred;
	while (curr)
	{
		open_red(data, curr);
		curr = curr->next;
	}
}

void last_in_out(t_cmds *cmd, t_list **infile, t_list **outfile)
{
    t_list *list = cmd->allred;
    while (list)
    {
        if (list->type == LEFT_HER || list->type == LEFT_RED)
            *infile = list;
        if (list->type == RIGHT_RED || list->type == RIGHT_HER)
            *outfile = list;
        list = list->next;
    }
}

int duplication(t_data *data, t_cmds *cmd)
{
    t_list *infile = NULL;
    t_list *outfile = NULL;
    int fd;

    files_manager(data, cmd);
    last_in_out(cmd, &infile, &outfile);
    if (infile != NULL)
    {
        fd = open(infile->content, O_RDONLY);
        if (fd == -1)
            errors(data, strerror(errno), 1);
        dup2(fd, 0);
        close(fd);
    }
    else if (infile == NULL && cmd->pipein != -1)
          dup2(cmd->pipein, 0);
    if (outfile != NULL)
    {
        fd = -1;
        if (outfile->type == RIGHT_HER)
            fd = open(outfile->content, O_RDWR | O_APPEND);
        else 
            fd = open(outfile->content, O_RDWR | O_TRUNC);
        if (fd == -1)
            errors(data, strerror(errno), 1);
        dup2(fd, 1);
        close(fd);
    }
    else if (outfile == NULL && cmd->pipeout != -1)
          dup2(cmd->pipeout, 1);
    return 0;
}
