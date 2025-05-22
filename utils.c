#include "minishell.h"

void errors(t_data *data, char *error, int exitcode)
{
	ft_putstr_fd(error, 1);
	free_data(data);
	exit(exitcode);
}

char	*ft_strjoin_fc(char *str, char *buff, int choice)
{
	char	*new;

	if (!str || !buff)
		return (NULL);
	new = ft_strjoin(str, buff);
	if (choice == 1 || choice == 3)
		free(str);
	if (choice == 2 || choice == 3)
		free(buff);
	return (new);
}

int in_set(char *set, char c)
{
	int i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void printdoule(char **str)
{
	if(!str || !*str)
		return ;
	int i = 0;
	while(str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
}