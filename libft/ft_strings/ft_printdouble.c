#include "../libft.h"

void ft_printdoule(char **str)
{
	if(!str || !*str)
		return ;
	int i = 0;
	while(str[i])
	{
		ft_putstr(str[i]);
		i++;
	}
}
