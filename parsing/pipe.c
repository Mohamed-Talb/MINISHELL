#include "../minishell.h"

int hpipe(t_data *data, t_dlist *token, char **line)
{
	char *s;

	s = *line;
	if(ft_strlen(token->content) != 0)
		ft_dlstback(&data->cmd_list, ft_strdup(""));
	token = ft_dlstlast(data->cmd_list);
	if (!(ft_strcmp(token->prev->content, "|")))
	{
		printf("errro\n");
		exit(1);
	}
	token->content = ft_append(token->content, *s, -1);
	*line = s;
	return 0;
}
