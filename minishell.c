#include "minishell.h"

/* function to be completed, lacking history appending, space appending to the readline return, handling another pipe '|' inside the readline */
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

/* needs to print prompt to stderr, and redirect readline to /dev/tty, and handle other readline errors such as pasting multiple time on the same line without runing clear before */
void prompter(t_data *data)
{
	char *str;

	str = "\e[1;96m⟦ minishell ⟧\e[0m \e[1;92m>>\e[0m ";
	if (data->last_exit_status != 0)
		str = ft_strjoin_fc("\e[1;96m⟦ minishell ⟧\e[0m\e[38;5;246m ", ft_strjoin_fc(ft_itoa(data->last_exit_status), "\e[0m\e[1;91m >>\e[0m ", 1), 2);
	rl_replace_line("", 0);    // optional: clears current input
	rl_on_new_line();          // required: signals readline             // i have no idea what i am doing with these 3 lines, but we will need them eventually
	// rl_redisplay();            // redraws the prompt + line
	data->line = readline(str); // this is printed in stderr!!
	add_history(data->line);
	
}

void minishell(t_data *data)
{
	while(1)
	{
		signals(1);
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
		if (data->pipes_nb == 1 && data->cmds[0]->flags && check_builtin(data->cmds[0]->flags[0]))
		{
			execute_builtin(data, data->cmds[0]);
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
