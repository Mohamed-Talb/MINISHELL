#include "minishell.h"

// int child(int infile, char **cmd, int outfile)
// {

// }

int heredoc(char *eof)
{
    (void) eof;
    return (0);
}

void starter(int pipein, t_data *data, t_cmds *fullcmd, int pipeout)
{
    (void) data;
    t_dlist *curr;

    if (fullcmd->inred != NULL)
    {
        curr = fullcmd->inred;
        while (curr != NULL)
        {
            if (curr->type == LEFT_RED)
            {
                if(pipein != -1)
                    close(pipein);
                pipein = open(curr->content, O_RDONLY);
            }
            else if (curr->type == LEFT_HER)
            {
                if(pipein != -1)
                    close(pipein);
                pipein = heredoc(curr->content);
            }
            curr = curr->next;
        }
    }
    if (fullcmd->outred != NULL)
    {
        curr = fullcmd->outred;
        while (curr != NULL)
        {
            if (curr->type == RIGHT_RED)
            {
                if(pipeout != -1)
                    close(pipeout);
                pipeout = open(curr->content, O_WRONLY | O_CREAT | O_TRUNC);
            }
            else if (curr->type == RIGHT_HER)
            {
                if(pipeout != -1)
                    close(pipeout);
                pipeout = open(curr->content, O_WRONLY | O_CREAT | O_APPEND);
            }
            curr = curr->next;
        }
    }
    fullcmd->pipein = pipein;
    fullcmd->pipeout = pipeout;
    // pipex(pipein, data, fullcmd, pipeout);
    // close(pipein); close(pipeout);
}

void redir_setup(t_data *data)
{
    int i;
    int pipefd[2];
    int prevfd = -1;

    i = 0;
    while (i < data->pipes_nb)
    {
        if (pipe(pipefd) == -1)
        {
            errors(data, "pipe");
        }
        if (i == 0 && data->pipes_nb > 1)
        {
            starter(prevfd, data, data->cmds[i], pipefd[1]); // we will then close after each exec to avoid hanging
            prevfd = pipefd[0];
        }
        else if (i == 0 && data->pipes_nb == 1)
        {
            close(pipefd[0]);
            close(pipefd[1]);
            starter(-1, data, data->cmds[i], -1);
            break;
        }
        else if (i != data->pipes_nb - 1)
        {
            starter(prevfd, data, data->cmds[i], pipefd[1]);
            prevfd = pipefd[0];
        }
        else
        {
            close(pipefd[0]);
            close(pipefd[1]);
            starter(prevfd, data, data->cmds[i], -1);
        }
        i++;
    }
}
