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

char *margs_printf(char *s, va_list args)
{
    char *result;
	char *ptr;
    
    result = NULL;
    while (*s)
    {
        if (*s == '%')
        {
            s++;
            if (*s == 'c')
                result = fappend(result, va_arg(args, int));
            else if (*s == 'd' || *s == 'i')
                result = ft_strjoin_es(result, ft_itoa(va_arg(args, int)), 3);
            else if (*s == 's')
                result = ft_strjoin_es(result, va_arg(args, char *), 1);
            else if (*s == 'f')
            {
				ptr = va_arg(args, char *);
                result = ft_strjoin_es(result, ptr, 1);
                ft_free(ptr);
            }
            s++;
        }
        else
            result = fappend(result, *s++);
    }
    return (result);
}

char *mprintf(char *s, ...)
{
	va_list	args;
	char *result;

	va_start(args, s);
	result = margs_printf(s, args);
	va_end(args);
	return (result);
}

int eputf(char *s, ...)
{
	va_list	args;
	char *result;
	int len;

	va_start(args, s);
	result = margs_printf(s, args);
	ft_putstr_fd(result, 2);
	len = ft_strlen(result);
	ft_free(result);
	va_end(args);
	return (len);
}

int ft_printf(char *s, ...)
{
	va_list	args;
	char *result;
	int len;

	va_start(args, s);
	result = margs_printf(s, args);
	ft_putstr_fd(result, 1);
	len = ft_strlen(result);
	ft_free(result);
	va_end(args);
	return (len);
}

// errcln: ERRor CLeaN
// will print the error to stderr then free memory
void errcln(int exitcode, char *error, ...)
{
	char *result;
	
	if (error)
	{
		va_list	args;
		va_start(args, error);
		result = margs_printf(error, args);
		ft_putstr_fd(result, 2);
		va_end(args);
		ft_free(result);
	}
	// free_all_adresses(); causes double free now, but necessary later
	exit(exitcode);
}

void set_errors(t_data *data, char *error, int exitcode)// change the prototype .... (mtaleb)
{
	ft_lstlast(data->cmd_list)->error = error;
	data->last_exit_status = exitcode;
}
