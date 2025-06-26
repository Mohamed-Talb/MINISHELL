#include "../minishell.h"

int get_sign(char *nptr)
{
	int sign;

	sign = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (!nptr[0])
			return (0);
	}
	else if (!ft_isdigit(*nptr))
		return (0);
	while (ft_isdigit(*nptr))
		nptr++;
	if (!((*nptr > 8 && *nptr < 14) || *nptr == 32 || *nptr == 0))
		return (0);
	return (sign);
}

unsigned long long ft_atoi_l(char *nptr)
{
	unsigned long long result;

	if (get_sign(nptr) == 0)
		return (L_OVERFLOW + 1ULL);
	result = 0;
	while (!ft_isdigit(*nptr))
		nptr++;
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *nptr - 48;
		nptr++;
	}
	return (result);
}

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
	result = checker(ft_atoi_l(argv[1]), get_sign(argv[1]), argv[1]);
	if (result == NUMREQ_CODE)
		return (2);
	if (argc > 2)
	{
		eputf(EXCESS_ARGS_ERR);
		return (-1);
	}
	return (result);
}
