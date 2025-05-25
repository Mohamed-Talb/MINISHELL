#include "../minishell.h"

void inred(t_data *data, t_dlist *node)
{
	int fd;
    if (node->type == RIGHT_HER)
	    fd = open(node->content, O_RDWR | O_CREAT | O_APPEND , 0644);
	else if (node->type == RIGHT_RED)
        fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
    else
	    fd = open(node->content, O_RDONLY, 0644);
	if (fd == -1)
		errors(data, MALLOC_ERROR, 1);
    close (fd);
}


void files_manager(t_data *data, t_cmds *cmd)
{
	t_dlist *curr;

	curr = cmd->allred;
	while (curr)
	{
		inred(data, curr);
		curr = curr->next;
	}
}
void last_in_out(t_cmds *cmd, t_dlist *infile, t_dlist *outfile)
{
    t_dlist *list = cmd->allred;
    while (list)
    {
        if (list->type == LEFT_HER || list->type == LEFT_RED)
            infile = list;
        if (list->type == RIGHT_RED ||list->type == RIGHT_HER)
            outfile = list;
        list = list->next;
    }
}

int duplication(t_data *data, t_cmds *cmd)
{
    t_dlist *infile = NULL;
    t_dlist *outfile = NULL;

    files_manager(data, cmd);
    last_in_out(cmd, infile, outfile);
    if (infile != NULL)
    {
        int infd = open(infile->content, O_RDONLY);
        if (infd == -1)
            errors(data, strerror(errno), 1);
        dup2(infd, 0);
    }
    else if (infile == NULL && cmd->pipein != -1)
          dup2(cmd->pipein, 0);
    if (outfile != NULL)
    {
        int outfd = -1;
        if (outfile->type == RIGHT_HER)
            outfd = open(outfile->content, O_RDWR | O_APPEND);
        else 
            outfd = open(outfile->content, O_RDWR | O_TRUNC);
        if (outfd == -1)
            errors(data, strerror(errno), 1);
        dup2(outfd, 1);
    }
    else if (outfile == NULL && cmd->pipeout != -1)
          dup2(cmd->pipeout, 1);
    return 0;
}
