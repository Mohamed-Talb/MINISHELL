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