
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

int double_q()
{
	return (0);
}

int handle_arg(t_data *data, t_dlist *token, char **line)
{
	char *s;

	s = *line;
	while (*s != '\0' && !ft_iswhitespace(*s))
	{
		if (*s == '\'')
			token->content = single_q(data, token->content, &s);
		else if(*s == '$')
			token->content = expand(data, token->content, &s);
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
	while (1)
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
}

int main()
{
	t_data *data = calloc(1, sizeof(data));

	data->line = ft_strdup("./'mini shell' hello world 'haha nigga \"$USER\"' $USER $HOME/file lol!");
	parser(data, data->line);
	ft_dlstiter(data->cmd_list, f);
}
