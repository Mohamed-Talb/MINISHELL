#include "../libft.h"

char *ft_remove(char *str, int pos)
{
	int i = 0;
	int j = 0;
	if(!str)
		return NULL;
	char *ptr = ft_malloc(ft_strlen(str));
	while (str[i])
	{
		if(i == pos)
		{
			i++;
			continue ; 
		}
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = 0;
	return ptr;
}