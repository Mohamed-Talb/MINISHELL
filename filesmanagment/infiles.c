#include  "../minishell.h"

void inred(t_data *data, t_dlist *node)
{
	int fd;
	fd = open(node->content, O_RDONLY, 0644);
	if (!fd)
		errors(data, MALLOC_ERROR, 1);
}


void	heredoc(t_data *data, t_dlist *node)
{
	char	*cmp;
	char	*line;
	int		fd;

	cmp = ft_strjoin(node->content, "\n");
	if (!cmp)
		errors(data, MALLOC_ERROR, 1);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!fd)
		errors(data, MALLOC_ERROR, 1);
	line = readline("> ");
	while (line && ft_strcmp(line, cmp))
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (cmp)
		free(cmp);
	free(line);
	close(fd);
}

void infiles_manager(t_data *data)
{
	t_dlist *curr;
	int i = data->index;
	char *currinfile;
	
	curr = data->cmds[i]->inred;
	while (curr)
	{
		if(curr->type == LEFT_HER)
		{
			heredoc(data, curr);
		}
		curr = curr->next;
	}
	curr = data->cmds[i]->inred;
	while (curr)
	{
		if(curr->type == LEFT_RED)
			inred(data, curr);
		curr = curr->next;
	}
	curr =  ft_dlstlast(data->cmds[i]->inred);
	currinfile = ft_strdup(curr->content);
	ft_dlstclear(&data->cmds[i]->inred);
	ft_dlstback(&data->cmds[i]->inred, currinfile); 
}
