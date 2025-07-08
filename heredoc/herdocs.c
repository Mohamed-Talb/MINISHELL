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

char *getexline(t_data *data, char *line) // move this is function to herdocexpand.c
{
    char *newline;
    char *exvalue;

    if (ft_strchr(line, '$'))
    {
		newline = ft_strdup("");
        while (*line)
        {
            if(*line == '$')
            {
				exvalue = herexpand(data, &line);
			    newline = ft_strjoin_es(newline, exvalue, 0);
            }
            else
            {
                newline = ft_append(newline, *line, -1);
                line++;
            }
        }
		return newline;
    }
	else
		return line;
}

void heredoc(t_data *data, t_list *node)
{
	int expand = 0;
    char    *rname;
    char	*line;
	char 	*del;
	int		fd;
    int     id;

    rname = getname();
	fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
	del = getdelemiter(data, node->content);
	printf("%s\n", del);
    id = fork();
    if (id == 0)
    {
        signals(3);
        line = readline(">>>> ");
        while (line && ft_strcmp(del, line))
        {
            if (expand == 0)
            line = getexline(data, line);
            ft_putstr_fd(line, fd);
            ft_putstr_fd("\n", fd);
            free(line);
            line = readline(">>>> ");
        }
        exit(0);
    }
    wait(NULL);
	close(fd);
	free(del);
    free(node->content);
    node->content = rname;
}
