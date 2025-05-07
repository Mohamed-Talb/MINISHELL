#include "minishell.h"

int main()
{
	char *line;
	t_data *data;
	
	data = init_data();
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
