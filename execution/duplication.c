#include "../minishell.h"

void ambiguous_redirect(t_data *data, t_list *node)
{
    char *content;
    char *tmp;
    char *exvalue;

    if (ft_strchr(node->content, '$'))
    {
        content = ft_strdup(node->content);
        tmp = content;
        free(node->content);
        node->content = NULL;
        while (*content)
        {
            if(*content == '$')
            {
                exvalue = dupexpand(data, &content);
                node->content = ft_strjoin_es(node->content, exvalue, 3);
            }
            else
            {
                node->content = ft_append(node->content, *content, -1);
                content++;
            }
        }
        free(tmp);
    }
}

void open_red(t_data *data, t_list *node)
{
	int fd;
    char *error;
    ambiguous_redirect(data , node);
    if (node->type == RIGHT_HER)
	    fd = open(node->content, O_RDWR | O_CREAT | O_APPEND , 0644);
	else if (node->type == RIGHT_RED)
        fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
    else
	    fd = open(node->content, O_RDONLY);
	if (fd == -1)
    {
        error = ft_strjoin("minishell: ", node->content);
        perror(error);
		errcln(data, 1, NULL);
    }
    close (fd);
}

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
