#include "../minishell.h"

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
	else if (*s == '\0' || ft_iswhitespace(*s))
	{
		token = ft_append(token, '$', -1);
		*line = s;
		return (token);
	}
	while (ft_isalnum(*s) || *s == '_')
	{
		env_var = ft_append(env_var, *s, -1);
		s++;
	}
	result = getenv(env_var);
	if (result != NULL)
	{
		token = ft_strjoin_fc(token, result, 1);
	}
	free(env_var);
	*line = s;
	return (token);
}
