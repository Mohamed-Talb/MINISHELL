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

void inred(t_data *data, t_dlist *node)
{
	int fd;
    if (node->type == RIGHT_HER)
	    fd = open(node->content, O_RDWR | O_CREAT | O_APPEND , 0644);
	else if (node->type == RIGHT_RED)
        fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
    else
	    fd = open(node->content, O_RDONLY, 0644);
	if (!fd)
		errors(data, MALLOC_ERROR, 1);
}

char *getname()
{
    char *rnbr;
    
    rnbr = randomnbr();
    char *randomname;
    randomname = ft_strjoin("/tmp/herdoc_", rnbr);
    return randomname;
}

void heredoc(t_data *data, t_dlist *node)
{
	char	*line;
    char    *rname;
	int		fd;


    rname = getname();
	fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
	if (!fd)
		errors(data, MALLOC_ERROR, 1);
	line = readline(">>>> ");
	while (line && ft_strcmp(node->content, line))
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline(">>>> ");
	}
	free(line);
	close(fd);
    free(node->content);
    node->content = rname;
}

void files_manager(t_data *data, t_cmds *cmd)
{
	t_dlist *curr;

	curr = cmd->allred;
	while (curr)
	{
		if(curr->type == LEFT_HER)
			heredoc(data, curr);
		curr = curr->next;
	}
	curr = cmd->allred;
	while (curr)
	{
		if(curr->type != LEFT_HER)
			inred(data, curr);
		curr = curr->next;
	}
}

int duplication(t_data *data, t_cmds *cmd)
{
    t_dlist *infile = NULL;
    t_dlist *outfile = NULL;

    files_manager(data, cmd);
    t_dlist *list = cmd->allred;
    while (list)
    {
        if (list->type == LEFT_HER || list->type == LEFT_RED)
            infile = list;
        if (list->type == RIGHT_RED ||list->type == RIGHT_HER)
            outfile = list;
        list = list->next;
    }
    if (infile != NULL)
    {
        int infd = open(infile->content, O_RDONLY);
        dup2(infd, 0);
    }
    else if (infile == NULL && cmd->pipein != -1)
    {
          dup2(cmd->pipein, 0);
    }
    if (outfile != NULL)
    {
        int outfd = -1;
        if (outfile->type == RIGHT_HER)
        {
            outfd = open(outfile->content, O_RDWR | O_APPEND);
        }
        else 
            outfd = open(outfile->content, O_RDWR | O_TRUNC);
        dup2(outfd, 1);
    }
    else if (outfile == NULL && cmd->pipeout != -1)
    {
          dup2(cmd->pipeout, 1);
    }
    return 0;
}
