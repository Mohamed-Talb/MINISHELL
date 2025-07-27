#include "../minishell.h"

void errors(char *error, int exitcode)
{
	ft_putstr_fd(error, 2);
	free_all_adresses();
	exit(exitcode);
}

// void set_errors(t_data *data, char *error, int exitcode)
// {
// 	ft_lstlast(data->cmd_list)->error = error;
// 	data->exit_code = exitcode;
// }

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

// int ft_printf(char *s, ...)
// {
// 	va_list	args;
// 	char *result;
// 	int len;

// 	va_start(args, s);
// 	result = margs_printf(s, args);
// 	ft_putstr_fd(result, 1);
// 	len = ft_strlen(result);
// 	ft_free(result);
// 	va_end(args);
// 	return (len);
// }

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
	free_all_adresses();
	exit(exitcode);
}
