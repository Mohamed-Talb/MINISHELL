#include "../minishell.h"

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
	char	*line;
    char    *rname;
	int		fd;
	char 	*del;
	int expand = 0;

    rname = getname();
	fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
	del = getdelemiter(data, node->content, &expand);
		printf("%s\n", del);
	line = readline(">>>> ");
	while (line && ft_strcmp(del, line))
	{
		if (expand == 0)
		line = getexline(data, line);
		// printf("%s\n", line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline(">>>> ");
	}
	close(fd);
	free(del);
	free(line);
    free(node->content);
    node->content = rname;
}

void open_herdocs(t_data *data, t_list *node)
{
	if (node->type == LEFT_HER)
		heredoc(data, node);
}
