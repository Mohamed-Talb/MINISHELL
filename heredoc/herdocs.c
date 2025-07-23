#include "../minishell.h"

char *randomnbr()
{
    int fd;
    int buff[11];
    unsigned int sum = 0;
    int i;

    fd = open("/dev/random", O_RDONLY);
    read(fd, buff, 5);
    i = 0;
    buff[5] = 0;
    while(i < 5)
    {
        sum += buff[i];
        i++;
    }  
    char *str = ft_uitoa(sum);
    return (str);
}

char *getname()
{
    char *rnbr;
    
    rnbr = randomnbr();
    char *randomname;
    randomname = ft_strjoin("/tmp/herdoc_", rnbr);
    return randomname;
}

void fill_herdoc(t_data *data, t_list *node, int fd)
{
    char *line;
    char *delemiter;
    
    delemiter = getdelemiter(data, node->content);
    while (1)
    {
        line = readline(">>> ");
        if (!line)
        {
            eputf("warning: here-document delimited by end-of-file (wanted `%s`)\n"
                    , delemiter);
            break;
        }
        if (ft_strcmp(delemiter, line) == 0)
        {
            ft_free(line);
            break;
        }
        if (ft_strchr(node->content, '\''), ft_strchr(node->content, '"'))
            line = getexline(data, line);
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        ft_free(line);
    }
}

int  heredoc(t_data *data, t_list *node)
{
    char    *rname;
	int		fd;
    int     id;
    int     status;
    signal_state(1);

    signal(SIGINT, SIG_IGN);
    rname = getname();
	fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
    id = fork();
    if (id == 0)
    {
        signals();
        fill_herdoc(data, node, fd);
        exit(0);
    }
    wait(&status);
    signals();
    signal_state(0);
    if (exitestatus(status))
    {
        close(fd);
        data->last_exit_status = exitestatus(status);
        return (1);
    }
    node->content = rname;
    return 0;
}

int openallherdocs(t_data *data)
{
    int i = 0;
    t_list *allred;
    while(data->cmds[i])
    {   
        allred = data->cmds[i]->allred;
        while(allred)
        {
            if (allred->type == LEFT_HER)
                if (heredoc(data, allred) == 1)
                {
                    reset_data(data);
                    return (1);
                }
            allred = allred->next;
        }
        i++;
    }
    return 0;
}