#include "../minishell.h"

static char  *check_cases(t_data *data, char **line)
{
    char *s = *line + 1;
    char *exvalue = ft_strdup("");
	if (*s == '\0' || ft_iswhitespace(*s))
	{
		exvalue = ft_append(exvalue, '$', -1);
	}
	else if (*s == '?')
	{
		char *status = ft_itoa(data->last_exit_status);
		exvalue = ft_strjoin_fc(exvalue, status, 3);
		s++;
	}
	else if (*s == '$')
	{
		exvalue = ft_strjoin_fc(exvalue, "$$", 1);
	    s++;
	}
	else if (*s == '\'' || *s == '"')
        return (exvalue);
    *line = s;
	return (exvalue);
}

char *dupexpand(t_data *data, char **line)
{
	char *env_var;
	char *result = NULL;
    char *exvalue = NULL;
    char *s;

    s = *line;
    exvalue = check_cases(data, &s);
	if (exvalue[0] != 0)
    {
        *line = s;
		return exvalue;
    }
	env_var = ft_strdup("");
	while (ft_isalnum(*s) || *s == '_')
	{
        env_var = ft_append(env_var, *s, -1);
		s++;
	}
	if (env_var[0] == 0)
	{
        exvalue = ft_append(exvalue, '$', -1);
		return exvalue;
	}
	result = ft_getenv(data->exported, env_var);
	exvalue = ft_strjoin_es(exvalue, result, 1);
    *line = s;
	free(env_var);
	return exvalue;
}