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

static char *expanddelemiter(char *token, char **line)
{
	char *s;

	s = *line + 1;
    if (*s == '\0')
        token = fappend(token, '$');
    else if (*s == '\'' || *s == '"')
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
            ret = expanddelemiter(ret, &s);
        else
            ret = fappend(ret, *s++);
    }
    return (ret);
}