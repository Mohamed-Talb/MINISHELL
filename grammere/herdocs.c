#include "../minishell.h"

char *getname()
{
    char *rnbr;
    
    rnbr = randomnbr();
    char *randomname;
    randomname = ft_strjoin("/tmp/herdoc_", rnbr);
    return randomname;
}


char *single_qh(t_data *data, char *token, char **line)
{
	char *s;

	s = *line + 1;
	while (*s != '\0' && *s != '\'')
	{
		token = ft_append(token, *s, -1);
		s++;
	}
	if (*s == '\'')
		s++;
	else
		errors(data, "minishell: syntax error: unclosed quote\n", 1);
	*line = s;
	return (token);
}


char *double_qh(t_data *data, char *token, char **line, int state)
{
	char *s;
	
	s = *line;
	s++;
	while(*s != '"' && *s != 0)
	{
		if(*s == '$' && state == 1 && *(s + 1) != '"')
		{
			// token = expand(data, token, &s);
		}
		else
		{
			token = ft_append(token, *s, -1);
			s++;
		}
	}
	if (*s == '"')
		s++;
	else
		errors(data, "minishell: syntax error: unclosed quote\n", 1);
	*line = s;
	return (token);
}

char *getdelemiter(t_data *data, char *s, int *expand)
{
	char *ret;

	ret = NULL;
	while (*s && !ft_iswhitespace(*s))
	{
		if (*s == '$')
		{
			s++;
			if (*s == '"')
			{
				*expand = 1;
				ret = double_qh(data, ret, &s, 0);
			}
			else if (*s == '\'')
			{
				*expand = 1;
				ret = single_qh(data, ret, &s);
			}
			else
			{
				ret = ft_append(ret, '$', -1);
			}
		}
		if (*s == '"')
		{
			*expand = 1;
			ret = double_qh(data, ret, &s, 0);
		}
		else if (*s == '\'')
		{
			*expand = 1;
			ret = single_qh(data, ret, &s);
		}
		else
		{
			ret = ft_append(ret, *s, -1);
			s++;
		}
	}
	return (ret);
}

void getexline(t_data *data, char *line)
{
    char *newline;
    char *exline;


    if (ft_strchr(newline, '$'))
    {
        while (*line)
        {
            if(*line == '$')
            {
                exline = herexpand(data, &line);
                newline = ft_strjoin_es(newline, exline, 3);
            }
            else
            {
                newline = ft_append(newline, *line, -1);
                line++;
            }
        }
    }
}

void heredoc(t_data *data, t_list *node)
{
	char	*line;
    char    *rname;
	int		fd;
	char 	*del;
	int expand = 0;

    rname = getname();
	fd = open(rname, O_WRONLY | O_CREAT | O_APPEND, 420);
	if (!fd)
		errors(data, strerror(errno), 1);
	del = getdelemiter(data, node->content, &expand);
	line = readline(">>>> ");
	while (line && ft_strcmp(del, line))
	{
		if (expand == 0)
		line = herdoc_expand(data, line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline(">>>> ");
	}
	close(fd);
	free(del);
	free(line);
    free(node->content);
    node->content = rname;
}

void open_herdocs(t_data *data, t_list *node)
{
	if (node->type == LEFT_HER)
		heredoc(data, node);
}
