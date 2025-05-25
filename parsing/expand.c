#include "../minishell.h"

char *expand(t_data *data, char *token, char **line)
{
	char *env_var = NULL;
	char *result;
	char *s = *line + 1;

	if (*s == '?')
	{
		token = ft_append(token, data->last_exit_status, -1);
		s++;
	}
	else if (ft_isdigit(*s) || *s == '\0' || ft_iswhitespace(*s))
	{
		token = ft_append(token, '$', -1);
		*line = s;
		return (token);
	}
	else if (*s == '\'' || *s == '\"')
	{
		*line = s;
		return (token);
	}
	else
	{
		while (ft_isalnum(*s) || *s == '_')
		{
			env_var = ft_append(env_var, *s, -1);
			s++;
		}
		if (env_var == NULL)
		{
			token = ft_append(token, '$', -1);
			*line = s;
			return (token);
		}
		result = getenv(env_var);
		if (result != NULL)
			token = ft_strjoin_fc(token, result, 1);
		free(env_var);
	}
	*line = s;
	return (token);
}

// echo $"test1""$USER"
	// test1mtaleb
