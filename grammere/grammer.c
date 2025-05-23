#include "../minishell.h"

int getredirections(t_data *data, t_dlist *list, int i)
{
	ft_dlstback(&(data->cmds[i]->allred), list->content);
	ft_dlstlast(data->cmds[i]->allred)->type = list->type;
	return 0;
}

int getcommand(t_data *data, t_dlist *list, int i)
{
	char **tmp = NULL;
	tmp = data->cmds[i]->cmd;
	int len = ft_strlen2(data->cmds[i]->cmd);
	data->cmds[i]->cmd = ft_append2(data->cmds[i]->cmd, list->content, len);
	if (tmp)
		ft_freedouble(&tmp);
	return 0;
}

void grammer(t_data *data)
{
	int i = 0;
	int type;
	init_cmds(data);
	t_dlist *list = (data->cmd_list);
	while(list)
	{
		type = list->type;
		if(type == PIPE)
			i++;
		else if(type == LEFT_HER || type == LEFT_RED || type == RIGHT_HER || type == RIGHT_RED)
			getredirections(data, list, i);	
		else
			getcommand(data, list, i);
		list = list->next;
	}
}
