#include "../minishell.h"

static char *check_cases(t_data *data, char **line)
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
    return exvalue;
}

char *herexpand(t_data *data, char **line, char *delimiter)
{
    char *s = *line;
    char *exvalue = check_cases(data, &s);
    char *var;

    if (exvalue[0] != 0)
    {
        *line = s;
        return exvalue;
    }
    var = ft_strdup("");
    while (ft_isalnum(*s) || *s == '_')
    {
        var = ft_append(var, *s, -1);
        s++;
    }
    if (var[0] == 0)
    {
        delimiter = ft_append(delimiter, '$', -1);
        free(var);
        *line = s;
        return delimiter;
    }
    delimiter = ft_strjoin_es(delimiter, var, 1);
    *line = s;
    free(var);
    return delimiter;
}

char *single_qh(t_data *data, char **line, char *delimiter)
{
    char *s = *line + 1;

    while (*s && *s != '\'')
    {
        delimiter = ft_append(delimiter, *s, -1);
        s++;
    }
    if (*s == '\'')
        s++;
    else
        errors(data, "minishell: syntax error: unclosed single quote\n", 1);

    *line = s;
    return delimiter;
}

char *double_qh(t_data *data, char **line, char *delimiter)
{
    char *s = *line + 1;

    while (*s && *s != '"')
    {
        if (*s == '$')
        {
            delimiter = herexpand(data, &s, delimiter);
        }
        else
        {
            delimiter = ft_append(delimiter, *s, -1);
            s++;
        }
    }
    if (*s == '"')
        s++;
    else
        errors(data, "minishell: syntax error: unclosed double quote\n", 1);

    *line = s;
    return delimiter;
}

char *getdelemiter(t_data *data, char *s, int *expand)
{
    char *ret = ft_strdup("");

    while (*s && !ft_iswhitespace(*s))
    {
        if (*s == '"')
        {
            *expand = 1;
            ret = double_qh(data, &s, ret);
        }
        else if (*s == '\'')
        {
            ret = single_qh(data, &s, ret);
        }
        else if (*s == '$')
        {
            *expand = 1;
            ret = herexpand(data, &s, ret);
        }
        else
        {
            ret = ft_append(ret, *s, -1);
            s++;
        }
    }
    return ret;
}
