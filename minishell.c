
#include "minishell.h"
#define PROMPT_DEFAULT "\001\e[1;96m\002\001⟦\002\x7f minishell \001⟧\002\x7f \001\e[0m\002\001\e[1;92m\002>>\001\e[0m\002 "
#define PROMPT_PREFIX "\e[1;96m⟦ minishell ⟧\e[0m\e[38;5;246m "
#define PROMPT_SUFFIX "\e[0m\e[1;91m >>\e[0m "

void	prompter(t_data *data)
{
	char	*str;
	char	*line;

	if (data->last_exit_status == 0)
 	   str = PROMPT_DEFAULT;
	else
	{
		str = ft_strjoin_fc(ft_itoa(data->last_exit_status), PROMPT_SUFFIX, 1);
		str = ft_strjoin_fc(PROMPT_PREFIX, str, 2);
	}
	line = readline(str);
	if (!line) 
	{
		data->line = NULL;
		return;
	}
	data->line = line;
	add_history(data->line);
}

void minishell(t_data *data)
{
    while(1)
    {
        signals();
        signal_state(0);
        prompter(data);
        if (data->line == NULL)
            break;
        if (parser(data, data->line))
            continue ;
        if (data->command_count == 0)
            continue ; // continues should reset data
        grammer(data);
        if (openallherdocs(data))
            continue ;
        if (data->pipes_nb == 1 && data->cmds[0]->flags && check_builtin(data->cmds[0]->flags[0]))
        {
            builtin(data, data->cmds[0]);
        }
        else
        {
            parent(data);
        }
        reset_data(data);
    }
}

int main(int ac, char **av, char **penv)
{
    (void) ac;
    (void) av;
    t_data *data;
    data = init_data(penv);
    minishell(data);
    ft_putstr_fd("exit\n", 1);
    rl_clear_history();
    return (0);
}