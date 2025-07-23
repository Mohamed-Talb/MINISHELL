#include "../minishell.h"

t_list *parsing_illusion(t_data *data, char *line)
{
    t_data *clone;
    t_list *cmd_list;

    clone = ft_calloc(1, sizeof(t_data));
    clone->line = line;
    clone->env = data->env;
    clone->exported = data->exported;
    clone->last_exit_status = clone->last_exit_status;
    parser(clone, line);
    cmd_list = clone->cmd_list;
    free(clone->line);
    free(clone);
    return (cmd_list);
}

void getfilename(t_data *data, t_list *node)
{
    t_list *tokens;
    
    tokens = parsing_illusion(data, ft_strdup(node->content));
    if (ft_lstsize(tokens) != 1)
        errcln(1, AMBIGOUS_RED, node->content);
    node->content = ft_strdup(tokens->content);
    ft_lstclear(&tokens);
}

int openredfiles(t_data *data, t_list *node)
{
	int fd;
    char *error;

    if (node->type != LEFT_HER)
        getfilename(data , node);
    if (node->type == RIGHT_HER)
	    fd = open(node->content, O_RDWR | O_CREAT | O_APPEND , 0644);
	else if (node->type == RIGHT_RED)
        fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
    else
	    fd = open(node->content, O_RDONLY);
	if (fd == -1)
    {
        error = mprintf("minishell: %s: %s\n", node->content, strerror(errno));
		errcln(1, error);
    }
    return (fd);
}

void fds_manager(t_data *data, t_cmds *cmd)
{
    t_list *curr;
    int fd;

    curr = cmd->allred;
    while (curr)
    {
        fd = openredfiles(data, curr);
        if (curr->type == LEFT_HER || curr->type == LEFT_RED)
        {
            close(cmd->infd);
            cmd->infd = fd;
        }
        else if (curr->type == RIGHT_RED || curr->type == RIGHT_HER)
        {
            close(cmd->outfd);
            cmd->outfd = fd;
        }
        curr = curr->next;
    }
}

int duplication(t_data *data, t_cmds *cmd)
{
    fds_manager(data, cmd);
    if (cmd->infd != -1)
    {
        dup2(cmd->infd, 0);
        close(cmd->infd);
    }
    if (cmd->outfd != -1)
    {
        dup2(cmd->outfd, 1);
        close(cmd->outfd);
    }
    return (0);
}
