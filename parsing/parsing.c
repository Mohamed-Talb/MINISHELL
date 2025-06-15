#include "../minishell.h"

int handle_arg(t_data *data, t_dlist *token, char *s, int i)
{
	while (s[i] != '\0' && ft_iswhitespace(s[i]) == false)
	{
		if (s[i] == '\'')
			i = single_q(data, token, s, i);
		else if (s[i] == '"')
			i = double_q(data, token, s, i);
		else if(s[i] == '$')
			i = expand(data, token, s, i);
		else if (s[i] == '<' || s[i] == '>')
		{
			i = redirect(data, token, s, i);
			break;
		}
		else if (s[i] == '|')
		{
			i = hpipe(data, token, s, i);
			data->pipes_nb++;
			break;
		}
		else
		{
			token->content = ft_append(token->content, s[i], -1);
			i++;
		}
	}
	return (i);
}

int parser(t_data *data, char *line)
{
	int new_pipe;
	t_dlist *new;
	char *str;
	int i;

	i = 0;
	new_pipe = 1;
	while (line[i] != '\0')
	{
		if (ft_iswhitespace(line[i]) == false)
		{
			str = ft_strdup("");
			new = ft_dlstback(&data->cmd_list, str);
			if (str == NULL || new == NULL)
				errors(data, MALLOC_ERROR, 1);
			i = handle_arg(data, new, line, i);
			if (new->type != PIPE && new_pipe == 1)
			{
				data->command_count++;
				new_pipe = 0;
			}
			else
				new_pipe = 1;
		}
		else
			i++;
	}
	return (0);
}
