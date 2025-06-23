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

int ft_exit(int argc, char **argv, t_data *data)
{
	(void) data;
	unsigned char result;
	int sign;
	unsigned long long value;

	ft_putstr("exit\n");
	if (argc == 1)
		return (data->last_exit_status);
	sign = get_sign(argv[1]);
	if (sign == 0)
	{
		eputf("minishell: exit: %s: numeric argument required\n", argv[1]);
		return (2);
	}
	value = ft_atoi_l(argv[1]);
	if ((value == 9223372036854775808ULL && sign == 1)
		|| value > 9223372036854775808ULL)
	{
		eputf("minishell: exit: %s: numeric argument required\n", argv[1]);
		return (2);
	}
	if (value == 9223372036854775808ULL && sign == -1)
		value = (LLONG_MIN);
	else
		value = sign * ((long long) value);
	result = (unsigned char) value;
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	return (result);
}
