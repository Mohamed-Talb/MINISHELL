#include "../minishell.h"

static char  *check_cases(t_data *data, char **line)
{
    char *s = *line + 1;
    char *exvalue = ft_strdup("");

	if (*s == '\0' || ft_iswhitespace(*s) || *s == '\'' || *s == '"')
		exvalue = fappend(exvalue, '$');
	else if (*s == '?')
	{
		char *status = ft_itoa(data->exit_code);
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
		env_var = fappend(env_var, *s);
		s++;
	}
	if (env_var[0] == 0)
	{
		exvalue = fappend(exvalue, '$');
		return exvalue;
	}
	result = ft_getenv(data->exported, env_var);
	exvalue = ft_strjoin_es(exvalue, result, 1);
	*line = s;
	return exvalue;
}

char *get_expanded_line(t_data *data, char *line)
{
    char *newline;
    char *exvalue;

    if (ft_strchr(line, '$'))
    {
		newline = ft_strdup("");
        while (*line)
        {
            if (*line == '$')
            {
				exvalue = expandline(data, &line);
			    newline = ft_strjoin_es(newline, exvalue, 0);
            }
            else
            {
                newline = fappend(newline, *line);
                line++;
            }
        }
		return (newline);
    }
	else
		return (line);
}
