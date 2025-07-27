#include "../minishell.h"

t_list *creat_node(t_data *data)
{
	char *str;
	t_list* new;

	str = ft_strdup("");
	new = ft_lstback(&data->cmd_list, str);
	return (new);
}

char	*ft_strjoin_fc(char *str, char *buff, int choice)
{
	char	*new;

	if (!str || !buff)
		return (NULL);
	new = ft_strjoin(str, buff);
	if (choice == 1 || choice == 3)
		ft_free(str);
	if (choice == 2 || choice == 3)
		ft_free(buff);
	return (new);
}

char	*ft_strjoin_es(char *str, char *buff, int choice)
{
	char	*new;

	if (!str && !buff)
		new = ft_strjoin("", "");
	else if (!str)
		new = ft_strjoin("", buff);
	else if (!buff)
		new = ft_strjoin(str, "");
	else
		new = ft_strjoin(str, buff);
	if (choice == 1 || choice == 3)
		ft_free(str);
	if (choice == 2 || choice == 3)
		ft_free(buff);
	return (new);
}

void printdoule(char **str)
{
	if(!str || !*str)
		return ;
	int i = 0;
	while(str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void print_cmds(t_data *data)
{
	int i;

	i = 0;
	while (data->cmds[i])
	{
		printf("%s\n", data->cmds[i]->cmd);
		printdoule(data->cmds[i]->flags);
		i++;
	}
	printf("\n");
}



void set_errors(t_data *data, char *error, int exitcode)
{
	ft_lstlast(data->cmd_list)->error = error;
	data->exit_code = exitcode;
}
