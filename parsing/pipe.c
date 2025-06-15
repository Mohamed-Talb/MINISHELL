#include "../minishell.h"

int hpipe(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	if(ft_strlen(token->content) != 0)
		ft_lstback(&data->cmd_list, ft_strdup(""));
	token = ft_lstlast(data->cmd_list);
	// if (!(ft_strcmp(token->prev->content, "|")))
	// {                       
	// 	printf("errro\n");                                    // i will fix it !!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	// 	exit(1);
	// }
	token->content = ft_append(token->content, *s, -1);
	token->type = PIPE;
	*line = s;
	return 0;
}
