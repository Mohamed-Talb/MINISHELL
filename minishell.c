#include "minishell.h"

int main()
{
	t_data *data;
	
	data = init_data();
	if (data == NULL)
	{
		// N is sizeof(data) here
		ft_putstr_fd("minishell: xmalloc: failed to allocate N bytes", 1);
		return (1);
	}
	while (1)
	{
   	 	data->line = readline("\e[91m\e[1mminishell:\e[92m~$ \e[0m");
		// obviously exit is a built it cmd not handled like this
     	if (data->line == NULL || !ft_strncmp("exit", data->line, 4))
			break;
		add_history(data->line);
		parser(data);
    	free(data->line);
	}
	free_data(data);
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
    return (0);
}
