
#include "minishell.h"

char *expand(t_data *data, char *token, char **line)
{
	char *env_var;
	char *result;
	char *s;

	env_var = NULL;
	s = *line + 1;
	if (*s == '?')
	{
		token = ft_append(token, data->last_exit_status, -1);
		s++;
	}
	while (ft_isalnum(*s) || *s == '_')
	{
		env_var = ft_append(env_var, *s, -1);
		s++;
	}
	result = getenv(env_var);
	if (result != NULL)
	{
		ft_strjoin_px(&token, result, 1);
	}
	free(env_var);
	*line = s;
	return (token);
}

int hpipe(t_data *data, t_dlist *curr_arg,  int *i)
{
	if(ft_strlen(curr_arg->content) != 0)
		ft_dlstback(&data->cmd_list, ft_strdup(""));
	curr_arg = ft_dlstlast(data->cmd_list);
	if (!(ft_strcmp(curr_arg->prev->content, "|")))
	{
		printf("errro\n");
		exit(1);
	}
	curr_arg->content = ft_append(curr_arg->content, data->line[(*i)], -1);
	return 0;
}

char *single_q(t_data *data, char *token, char **line)
{
	char *s;

	s = *line + 1;
	while (*s != '\0' && *s != '\'')
	{
		token = ft_append(token, *s, -1);
		s++;
	}
	if (*s == '\'')
		s++;
	else
		errors(data, "minishell: syntax error: unclosed quote\n");
	*line = s;
	return (token);
}


int double_q(t_data *data, t_dlist *token, char **line)
{
	char *s;
	
	s = *line;
	while(*s != '"' && *s != 0)
	{
		if(*s == '$')
			token->content = expand(data, token->content, &s);
		token->content = ft_append(token->content, *s, -1);
	}
	return (0);
}

void redirect(t_data *data, t_dlist *token, char **line)
{
	char *s;

	s = *line;
	if (*s == '>')
	{
		token->type = RIGHT_RED;
		s++;
		if (*s == '>')
		{
			token->type = RIGHT_HER;
			s++;
		}
	}
	else if (*s == '<')
	{
		token->type = LEFT_RED;
		s++;
		if (*s == '<')
		{
			token->type = RIGHT_HER;
			s++;
		}
	}
}

int handle_arg(t_data *data, t_dlist *token, char **line)
{
	char *s;

	s = *line;
	while (*s != '\0' && !ft_iswhitespace(*s))
	{
		if (*s == '\'')
			token->content = single_q(data, token->content, &s);
		else if (*s == '"')
			double_q(data, token, &s);
		else if (*s == '<' || *s == '>')
			redirect(data, token, &s);
		else
		{
			token->content = ft_append(token->content, *s, -1);
			s++;
		}
	}
	*line = s;
	return (0);
}

int parser(t_data *data, char *line)
{
	while (*line != '\0')
	{
		if (!ft_iswhitespace(*line))
		{
			ft_dlstback(&data->cmd_list, ft_strdup(""));
			handle_arg(data, ft_dlstlast(data->cmd_list), &line);
		}
		if (*line == '\0')
			return (0);
		line++;
	}
	return (0);
}

int parser(t_data *data)
{
	int i;

	i = 0;
	while (1)
	{
		if (!ft_iswhitespace(data->line[i]))
		{
			ft_dlstback(&data->cmd_list, ft_strdup(""));
			handle_arg(data, &i);
		}
		if (data->line[i] == '\0')
			return (0);
		i++;
	}
}

int main()
{
	t_data data = {0};

	data.line = "echo hello \"world\"dcghdj|'haha nigga'lol!";
	parser(&data);
	ft_dlstiter(data.cmd_list, f);
}

