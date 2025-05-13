#include "minishell.h"

int main()
{
	t_data *data = malloc(sizeof(t_data));
	init_data(data);
	data->line = ft_strdup("./ < mmm $ 'HOME' mm 'mini shell' helloworld 'haha nigga \"$USER\"' $USER $HOME/file lol!");
	parser(data, data->line);
	ft_dlstiter(data->cmd_list, f);
}