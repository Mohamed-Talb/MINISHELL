char  *herdoc_expand(t_data *data, char *line)
{
	int i = 0;
	char *var = NULL;
	char *result = ft_strdup("");
	char *varvalue = NULL;
	if (line == NULL)
		return NULL;
	while(line[i]  != '$')
	{
		result = ft_append(result, line[i], -1);
		i++;
	}
	i++;
	if (line[i] == '?')
	{
		result = ft_append(line, data->last_exit_status, -1);
		i++;
	}
	else if (ft_isdigit(line[i]) || line[i] == '\0' || ft_iswhitespace(line[i]))
	{
		result = ft_append(result, '$', -1);
		return (result);
	}
	else if (line[i] == '\'' || line[i] == '\"')
	{
		return (result);
	}
	else
	{
		while (ft_isalnum(line[i]) || line[i] == '_')
		{
			var = ft_append(var, line[i], -1);
			i++;
		}
		if (var == NULL)
		{
			result = ft_append(result, '$', -1);
			i++;
			return (result);
		}
		varvalue = getenv(var);
		result = ft_strjoin_fc(result, varvalue, 1);
		free(var);
	}
	free(line);
	line = NULL;
	return (result);
}

/*
#include "../minishell.h"

int parsing_errors(t_data *data, t_list *list)
{
	if (!list)
	{
		reset_data(data);
		return (1);
	}
	while (list)
	{
		if (list->error)
		{
			ft_putstr_fd(list->error, 2);
			reset_data(data);
			return (1);
		}
		list = list->next;
	}
	return 0;
}

t_list *creat_node(t_data *data)
{
	char *str;
	t_list* new;

	str = ft_strdup("");
	new = ft_lstback(&data->cmd_list, str);
	if (str == NULL || new == NULL)
		errors(data, MALLOC_ERROR, 1);
	return (new);
}

t_list *handle_arg(t_data *data, t_list *token, char **line)
{
	char *s;

	s = *line;
	while (*s != '\0' && !ft_iswhitespace(*s))
	{
		if (*s == '$')
			expand(data, token, &s);
		else
		{
			if (token == NULL)
				token = creat_node(data);
			if (*s == '\'')
				single_q(data, token, &s);
			else if (*s == '"')
				double_q(data, token, &s, 1);
			else if (*s == '<' || *s == '>')
			{
				redirection(data, token, &s);
				continue ;
			}
			else if (*s == '|')
			{
				hpipe(data, token, &s);
				data->pipes_nb++;
				break ;
			}
			else
			{
				token->content = ft_append(token->content, *s, -1);
				s++;
			}
		}
	}
	*line = s;
	return (token);
}

int parser(t_data *data, char *line)
{
	t_list	*new;
	int		new_pipe;

	new_pipe = 1;
	while (*line != '\0')
	{
		if (ft_iswhitespace(*line) == false)
		{
			new = handle_arg(data, NULL, &line);
			if (new != NULL)
			{
				if (new->content != NULL && new->type != PIPE && new_pipe == 1)
				{
					data->command_count++;
					new_pipe = 0;
				}
				else
					new_pipe = 1;
			}
		}
		if (*line == '\0')
			break ;
		line++;
	}
	if (parsing_errors(data, data->cmd_list) == 1)
		return (1);
	return (0);
}

#include "../minishell.h"

bool check_cases(t_data *data, char **token, char *s, int *i)
{
	if (s[*i] == '\0' || ft_iswhitespace(s[*i]))
	{
		*token = ft_append(*token, '$', -1);
		return (true);
	}
	else if (s[*i] == '?')
	{
		char *status = ft_itoa(data->last_exit_status);
		*token = ft_strjoin_fc(*token, status, 3);
		(*i)++;
		return (true);
	}
	else if (s[*i] == '$')
	{
		*token = ft_strjoin_fc(*token, "$$", 1);
		(*i)++;
		return (true);
	}
	else if (s[*i] == '\'' || s[*i] == '"')
	{
		return (true);
	}
	return (false);
}

int hexpand(t_data *data, char **token, char *s)
{
	char *env_var = NULL;
	char *result = NULL;
	int i;

	i = 1;
	if (check_cases(data, token, s, &i))
		return (i);
	env_var = ft_strdup("");
	while (ft_isalnum(s[i]) || s[i] == '_')
	{
		env_var = ft_append(env_var, s[i], -1);
		i++;
	}
	if (env_var[0] == 0)
	{
		*token = ft_append(*token, '$', -1);
		return (i);
	}
	result = ft_getenv(data->exported, env_var);
	*token = ft_strjoin_es(*token, result, 1);
	free(env_var);
	return (i);
}

void expand(t_data *data, t_list *token, char **line)
{
	char *str;
	int i;

	(void) token;
	str = ft_strdup("");
	i = hexpand(data, &str, *line);
	eputf("str is: %s\n", str);
	(*line)+= i;
	i = 0;
	while (str[i])
	{
		if (ft_iswhitespace(str[i]))
			i++;
		else
		{
			while (str[i] && ft_iswhitespace(str[i]) != false)
			{
				if (token == NULL)
					creat_node();
				i++;
			}
		}
	}
}

*/
