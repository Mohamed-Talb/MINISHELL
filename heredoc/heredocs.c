#include "../minishell.h"

char *randomnbr()
{
    unsigned int buff;
    int fd;

    fd = open("/dev/random", O_RDONLY);
    if (fd < 0)
        errcln(EXIT_FAILURE, "minishell: open: %s\n", strerror(errno));
    read(fd, &buff, 4);
    close(fd);
    return (ft_uitoa(buff));
}

char *get_expanded_line(t_data *data, char **line)
{
    char *newline;
	char *s;
	
	s = *line;
	newline = ft_strdup("");
    while (*s)
	{
		if (*s == '$')
		{
			if (s[1] == '\'' || s[1] == '"')
				newline = fappend(newline, *s++);
			else
				*line = expand(data, *line, &s);
		}
		else
			newline = fappend(newline, *s++);
	}
	ft_free(*line);
	return (newline);
}

void fill_herdoc(t_data *data, t_list *node, char *rname)
{
    char    *delemiter;
    char    *line;
    int     fd;

    fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
    if (fd < 0)
    {
        eputf("minishell: open: %s\n", strerror(errno));
        errors(NULL, EXIT_FAILURE);
    }
    delemiter = getdelemiter(node->content);
    line = readline(HEREDOC_PROMPT);
    while (line != NULL && ft_strcmp(delemiter, line) != 0)
    {
        if (hasfrom_set(node->content, "'\"") == false)
            line = get_expanded_line(data, &line);
        line = fappend(line, '\n');
        ft_putstr_fd(line, fd);
        ft_free(line);
        line = readline(HEREDOC_PROMPT);
    }
    free_all_adresses();
    close(fd);
    exit(0);
}

int  heredoc(t_data *data, t_list *node)
{
    int     status;
    char    *rname;
    int     id;

    rname = ft_strjoin_fc("/tmp/herdoc_", randomnbr(), 2);
    signal(SIGINT, SIG_IGN);
    signal_state(1);
    id = fork();
    if (id == -1)
    {
        eputf( "minishell: fork: %s\n", strerror(errno));
        errors(NULL, EXIT_FAILURE);
    }
    if (id == 0)
    {
        signals();
        fill_herdoc(data, node, rname);
    }
    wait(&status);
    signals();
    signal_state(0);
    ft_free(node->content);
    node->content = rname;
    data->exit_code = exitestatus(status);
    return (data->exit_code);
}

int openallherdocs(t_data *data)
{
    t_list *allred;
    int i;

    i = 0;
    while (data->cmds[i])
    {   
        allred = data->cmds[i]->allred;
        while (allred)
        {
            if (allred->type == LEFT_HER)
            {
                if (heredoc(data, allred) != 0)
                    return (1);
            }
            allred = allred->next;
        }
        i++;
    }
    return (0);
}
