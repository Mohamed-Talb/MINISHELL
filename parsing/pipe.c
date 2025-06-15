#include "../minishell.h"

int hpipe(t_data *data, t_list *token, char *s, int i)
{
	// if(ft_strlen(token->content) != 0)
	// 	ft_lstback(&data->cmd_list, ft_strdup(""));
	// token = ft_lstlast(data->cmd_list); // why??!?!
    ft_lstiter(data->cmd_list, f);
	// if (!(ft_strcmp(token->prev->content, "|")))
	// {
	// 	printf("errro: %s\n", (char *) token->content);                               // waiting for the fix
	// 	exit(1);
	// }
	token->content = ft_append(token->content, s[i], -1);
	token->type = PIPE;
    i++;
	return (i);
}
