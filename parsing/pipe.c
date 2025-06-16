#include "../minishell.h"

void pipe_errors(t_data *data, char c)
{
	t_list *prev;
	char *strerror;

	prev = ft_lstprevlast(data->cmd_list);
	if (c == '|')
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "||'\n");
	else if (data->line[0] == '|' || !ft_strcmp(prev->content, "|"))
		strerror = ft_strjoin(UNEXPECTED_TOKEN, "|'\n");
	else 
		return ;
	set_errors(data, strerror, 1);
}
int hpipe(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	if(ft_strlen(token->content) != 0)
		ft_lstback(&data->cmd_list, ft_strdup(""));
	pipe_errors(data, *(s + 1));
	token = ft_lstlast(data->cmd_list);
	token->content = ft_append(token->content, *s, -1);
	token->type = PIPE;
	*line = s;
	return 0;
}
