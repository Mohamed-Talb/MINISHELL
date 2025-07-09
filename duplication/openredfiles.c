#include "../minishell.h"

static int is_ambiguous_red(t_data *data, char *expanded, char *original)
{
    (void)data;
    if (!expanded || expanded[0] == '\0' || ft_strchr(expanded, ' '))
    {
        eputf(AMBIGOUS_RED, original);
        exit(1);
    }
    return (0);
}

static void getfilename(t_data *data, t_list *node)
{
    char *content;
    char *tmp = NULL;
    char *exvalue;
    if (ft_strchr(node->content, '$'))
    {
        content = ft_strdup(node->content);
        tmp = content;
        node->content = NULL;
        while (*content)
        {
            if(*content == '$')
            {
                exvalue = dupexpand(data, &content);
                node->content = ft_strjoin_es(node->content, exvalue, 3);
            }
            else
            {
                node->content = ft_append(node->content, *content, -1);
                content++;
            }
        }
        is_ambiguous_red(data, node->content, tmp);
    }
}

int openredfiles(t_data *data, t_list *node)
{
	int fd;
    char *error;
    getfilename(data , node);
    if (node->type == RIGHT_HER)
	    fd = open(node->content, O_RDWR | O_CREAT | O_APPEND , 0644);
	else if (node->type == RIGHT_RED)
        fd = open(node->content, O_RDWR | O_CREAT | O_TRUNC , 0644);
    else
	    fd = open(node->content, O_RDONLY);
	if (fd == -1)
    {
        error = ft_strjoin("minishell: ", node->content);
        perror(error);
		errcln(data, 1, NULL);
    }
    return (fd);
}