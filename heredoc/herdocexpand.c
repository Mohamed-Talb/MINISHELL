#include "../minishell.h"

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

static char *expandline(t_data *data, char **line)
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
	return exvalue;
}

char *getexline(t_data *data, char *line)
{
    char *newline;
    char *exvalue;

    if (ft_strchr(line, '$'))
    {
		newline = ft_strdup("");
        while (*line)
        {
            if(*line == '$')
            {
				exvalue = expandline(data, &line);
			    newline = ft_strjoin_es(newline, exvalue, 0);
            }
            else
            {
                newline = ft_append(newline, *line, -1);
                line++;
            }
        }
		return newline;
    }
	else
		return line;
}
