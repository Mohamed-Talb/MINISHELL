#include "../minishell.h"

// errcln: ERRor CLeaN
// will print the error to stderr then free data
void errcln(t_data *data, int exitcode, char *error, ...)
{
	if (error)
	{
		va_list	args;
		va_start(args, error);
		veputf(error, args);
		va_end(args);
	}
	free_data(data);
	exit(exitcode);
}

void errors(t_data *data, char *error, int exitcode)
{
	ft_putstr_fd(error, 2);
	free_data(data);
	exit(exitcode);
}

void set_errors(t_data *data, char *error, int exitcode)// change the prototype .... (mtaleb)
{
	ft_lstlast(data->cmd_list)->error = error;
	data->last_exit_status = exitcode;
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
		free(str);
	if (choice == 2 || choice == 3)
		free(buff);
	return (new);
}

int in_set(char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int respects_set(char *str, char *set)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (in_set(set, str[i]) == 0)
			return (0);
		i++;
	}
	if (ft_strcmp(str, set) != 0)
		return (0);
	return (1);
}

int posin_set(char *set, char c)
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
		printf("%s\n", str[i]);
		i++;
	}
}

char *randomnbr()
{
    int fd;
    int buff[11];
    unsigned int sum = 0;
    int i;

    fd = open("/dev/random", O_RDONLY);
    read(fd, buff, 5);
    i = 0;
    buff[5] = 0;
    while(i < 5)
    {
        sum += buff[i];
        i++;
    }  
    char *str = ft_uitoa(sum);
    return (str);
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

// mfor_printf: function to malloc a ready to print string for ft_printf
char *mfor_printf(char *str, void *sarr[], int darr[])
{
    char *result;
    int i;
    int s;
    int d;

    s = 0;
    d = 0;
    i = 0;
    result = NULL;
    while (str[i])
    {
        if (str[i] == '%')
        {
            i++;
            if (str[i] == 'c')
                result = fappend(result, darr[d++]);
            else if (str[i] == 'd' || str[i] == 'i')
                result = ft_strjoin_es(result, ft_itoa(darr[d++]), 3);
            else if (str[i] == 's')
                result = ft_strjoin_es(result, sarr[s++], 1);
            else if (str[i] == 'f')
            {
                result = ft_strjoin_es(result, sarr[s], 1);
                free(sarr[s++]);
            }
            i++;
        }
        else
            result = fappend(result, str[i++]);
    }
    return (result);
}
