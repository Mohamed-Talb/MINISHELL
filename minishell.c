#include "minishell.h"
int main()
{
	t_data *data = malloc(sizeof(t_dlist));
	data->anything = 5

	t_data *data2;
	char *line;

	init_data(data);
	while (1)
	{
   	 	line = readline("shell>> ");
     	if (!line) 
		{
        	errors(data, "no input recieve\n");
        	return 1;
    	}
		printf("%s\n", line);
    	free(line);
	}
    return 0;
}