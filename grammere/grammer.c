#include "../minishell.h"

int getredirections(t_data *data, t_list *list, int i)
{
	if (list->type == LEFT_HER)
	{
		open_herdocs(data, list);
	}
	ft_lstback(&(data->cmds[i]->allred), list->content);
	ft_lstlast(data->cmds[i]->allred)->type = list->type;
	return 0;
}

int getcommand(t_cmds *command, t_list *list)
{
	char **tmp = NULL;
	int len;

	if (command->cmd)
	{
		tmp = command->flags;
		len = ft_strlen2(command->flags);
		command->flags = ft_append2(command->flags, list->content, len);
	}
	else
	{
		command->flags = ft_append2(command->flags, list->content, 0);
		command->cmd = ft_strdup(list->content); 
	}
	if (tmp)
		ft_freedouble(&tmp);
	return 0;
}

void grammer(t_data *data)
{
	int i;
	int type;

	i = 0;
	init_cmds(data);
	t_list *list = (data->cmd_list);
	while(list)
	{
		type = list->type;
		if (list->content == NULL)
		{
			list = list->next;
			continue ;
		}
		if(type == PIPE)
			i++;
		else if(type == LEFT_HER || type == LEFT_RED || type == RIGHT_HER || type == RIGHT_RED)
			getredirections(data, list, i);	
		else
			getcommand(data->cmds[i], list);
		list = list->next;
	}
}
