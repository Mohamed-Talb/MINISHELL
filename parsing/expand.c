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

int regular_expand(t_data *data, char **token, char *s)
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
		*token = fappend(*token, '$');
		return (i);
	}
	result = ft_getenv(data->exported, env_var);
	*token = ft_strjoin_es(*token, result, 1);
	return (i);
}

int expand(t_data *data, char **line)
{
	int expand_size;
	int old_size;
	char *str;
	int pos;
	int i;

	pos = *line - data->line;
	str = ft_substr(data->line, 0, pos);
	old_size = ft_strlen(str);
	i = regular_expand(data, &str, *line);
	expand_size = ft_strlen(str) - old_size;
	data->line = ft_strjoin_fc(str, *line + i, 1);
	*line = data->line + pos;
	data->expand_rage = *line + expand_size;
	return (expand_size);
}
