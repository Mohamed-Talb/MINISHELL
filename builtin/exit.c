#include "../minishell.h"

int checker(unsigned long long value, int sign, char *arg)
{
	if (sign == 0)
	{
		eputf(NUMREQ_ERR, arg);
		return (NUMREQ_CODE);
	}
	if ((value == L_OVERFLOW && sign == 1) || value > L_OVERFLOW)
	{
		eputf(NUMREQ_ERR, arg);
		return (NUMREQ_CODE);
	}
	if (value == L_OVERFLOW && sign == -1)
		value = (LLONG_MIN);
	else
		value = sign * ((long long) value);
	return ((unsigned char) value);
}

int ft_exit(int argc, char **argv, t_data *data)
{
	int result;

	((void) data, ft_putstr("exit\n"));
	if (argc == 1)
		return (data->last_exit_status);
	result = checker(ft_atoi_l(argv[1]), atoi_sign(argv[1]), argv[1]);
	if (result == NUMREQ_CODE)
		return (2);
	if (argc > 2)
	{
		eputf(EXCESS_ARGS_ERR);
		return (-1);
	}
	return (result);
}
