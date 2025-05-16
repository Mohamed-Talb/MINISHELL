#include "minishell.h"

// int main()
// {
// 	t_data *data = malloc(sizeof(t_data));

// 	init_data(data);
// 	while (1)
// 	{
// 		data->line = readline("\e[91m\e[1mminishell:\e[92m~$ \e[0m");
// 		// obviously exit is a built-in cmd not handled by comparison
// 		if (data->line == NULL || !ft_strncmp("exit", data->line, 4))
// 			break;
// 		add_history(data->line);
// 		parser(data, data->line);
// 		ft_dlstiter(data->cmd_list, f);
// 		free(data->line);
// 		ft_dlstclear(&data->cmd_list);
// 	}
// 	free_data(data);
// 	ft_putstr_fd("exit\n", 1);
// 	rl_clear_history();
// 	return (0);
// }
