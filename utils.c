#include "minishell.h"

void errors(t_data *data, char *error)
{
	ft_putstr_fd(error, 1);
	free_data(data);
	exit(1);
}

t_data *init_data()
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
	{
		errors(data, MALLOC_ERROR);
		return (NULL);
	}
	return (data);
}

char	*ft_strjoin_px(char **str, char *buff, int choice)
{
	char	*result;
	int		len1;
	int		len2;

	if (!str || !(*str) || !buff)
		return (NULL);
	len1 = ft_strlen(*str);
	len2 = ft_strlen(buff);
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, *str, len1);
	ft_memcpy(result + len1, buff, len2);
	result[len1 + len2] = 0;
	if (choice == 1 || choice == 3)
		free(*str);
	if (choice == 2 || choice == 3)
		free(buff);
	*str = result;
	return (*str);
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