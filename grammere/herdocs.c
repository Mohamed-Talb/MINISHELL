#include "../minishell.h"

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

void open_herdocs(t_data *data, t_dlist *node)
{
	if (node->type == LEFT_HER)
	    heredoc(data, node);
}