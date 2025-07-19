
#include "minishell.h"
#define PROMPT_DEFAULT "\001\e[1;96m\002\001⟦\002\x7f minishell \001⟧\002\x7f \001\e[0m\002\001\e[1;92m\002>>\001\e[0m\002 "
#define PROMPT_PREFIX "\e[1;96m⟦ minishell ⟧\e[0m\e[38;5;246m "
#define PROMPT_SUFFIX "\e[0m\e[1;91m >>\e[0m "

// Keep your existing signal functions unchanged
// int signal_state(int state)
// {
//     static int value;
//     if(state != -1)
//         value = state;
//     return value;
// }

// void hanlder(int sig)
// {
//     (void)sig;
//     if (signal_state(-1) == 0)
//     {
//         write(1, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
//     else if (signal_state(-1) == 1)
//     {
//         write(1, "\n", 1);
//         exit(130);
//     }
// }

// void signals()
// {
//     signal(SIGINT, hanlder);
//     signal(SIGQUIT, SIG_IGN);
// }

int completline(t_data *data)
{
    char *completline;
    int i;
    int j;
    i = 0;
    completline = NULL;
    if (data->line[0] != 0 && data->line[0] != '|')
    {
        i = ft_strlen(data->line) - 1;
        while (i >= 0 && ft_iswhitespace(data->line[i]))
            i--;
        j = i - 1;
        if (j == -1)
            return 0;
        while (j >= 0 && ft_iswhitespace(data->line[j]))
            j--;
        if (data->line[j] == '|')
            return 0;
        if (i >= 0 && data->line[i] == '|')
        {
            completline = readline("> ");
            while (completline && completline[0] == '\0')
            {
                free(completline);
                completline = readline("> ");
            }
            if (completline == NULL)
            {
                ft_putstr_fd("syntax error: unexpected end of input\n", 2);
                reset_data(data);
                return 1;
            }
            data->line = ft_strjoin_fc(data->line, completline, 3);
        }
    }
    return 0;
}

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
        if (completline(data))
            continue;
        if (parser(data, data->line))
            continue ;
        if (data->command_count == 0)
            continue ;
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