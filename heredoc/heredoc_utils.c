#include "../minishell.h"

char *geth_enclosed_text(char *token, char **line)
{
	char target;
	char *s;

	s = *line;
	target = *s++;
	while (true)
	{
		if (*s == '\0')
			return (NULL);
		if (*s == target)
		{
			s++;
			break;
		}
		token = fappend(token, *s++);
	}
	*line = s;
	return (token);
}

char *hexpand(char *token, char **line)
{
	char *s;

	s = *line + 1;
    if (*s == '\0')
        token = fappend(token, '$');
    if (*s == '\'' || *s == '"')
        token = geth_enclosed_text(token, &s);
    else
    {
        token = fappend(token, '$');
        token = fappend(token, *s++);
    }
	*line = s;
	return (token);
}

char *getdelemiter(t_data *data, char *s)
{
    char *ret;

    (void) data;
    ret = ft_strdup("");
    while (*s != '\0' && ft_iswhitespace(*s) == false)
    {
        if (*s == '\'' || *s == '"')
            ret = geth_enclosed_text(ret, &s);
        else if (*s == '$')
            ret = hexpand(ret, &s);
        else
            ret = fappend(ret, *s++);
    }
    return (ret);
}

static char  *check_cases(t_data *data, char **line)
{
    char *s = *line + 1;
    char *exvalue = ft_strdup("");

	if (*s == '\0' || ft_iswhitespace(*s) || *s == '\'' || *s == '"')
		exvalue = ft_append(exvalue, '$', -1);
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
    *line = s;
	return (exvalue);
}

char *herexpand(t_data *data, char **line)
{
	char *env_var;
	char *result = NULL;
    char *exvalue;
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