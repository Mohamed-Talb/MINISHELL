#include "../minishell.h"

void pipe_errors(t_data *data, char c)
{
	t_list *prev;
	char *strerror;

	prev = ft_lstlast(data->cmd_list);
	if (c == '|')
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "||'\n");
	else if (data->line[0] == '|' || !ft_strcmp(prev->content, "|"))
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "|'\n");
	else 
		return ;
	set_errors(data, strerror, 2);
}

t_list	*hpipe(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	token = creat_node(data);
	pipe_errors(data, *(s + 1));
	token->content = fappend(token->content, *s++);
	token->type = PIPE;
	token = NULL;
	data->pipes_nb++;
	*line = s;
	return (token);
}
