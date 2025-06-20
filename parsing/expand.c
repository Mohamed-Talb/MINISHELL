#include "../minishell.h"

bool check_cases(t_data *data, t_list *token, char **s)
{
	if (**s == '\0' || ft_iswhitespace(**s))
	{
		token->content = ft_append(token->content, '$', -1);
		return true;
	}
	else if (**s == '?')
	{
		char *status = ft_itoa(data->last_exit_status);
		token->content = ft_strjoin_fc(token->content, status, 3);
		(*s)++;
		return true;
	}
	else if (**s == '$')
	{
		token->content = ft_strjoin_fc(token->content, "$$", 1);
		(*s)++;
		return true;
	}
	else if (**s == '\'' || **s == '"')
	{
		return true;
	}
	return false;
}

void expand(t_data *data, t_list *token, char **line)
{
	char *env_var = NULL;
	char *result = NULL;
	char *s = *line + 1;

	if (check_cases(data, token, &s))
	{
		*line = s;
		return;
	}
	env_var = ft_strdup("");
	while (ft_isalnum(*s) || *s == '_')
	{
		env_var = ft_append(env_var, *s, -1);
		s++;
	}
	if (env_var[0] == 0)
	{
		token->content = ft_append(token->content, '$', -1);
		*line = s;
		return ;
	}
	result = ft_getenv(data->env, env_var);
	// if (result == NULL && mode == 3)
	// 	token->content = ft_strjoin_fc(token->content, "", 1);
	// else
	// 	token->content = ft_strjoin_fc(token->content, result, 1);
	token->content = ft_strjoin_es(token->content, result, 1);
	free(env_var);
	*line = s;
}

// void expand(t_data *data, t_list *token, char **line)
// {
//     t_list	*new;
// 	char 	*str;
//     char *old_s;

//     (void) token;
//     old_s = *line;
// 	str = ft_strdup("");
// 	new = ft_lstback(&data->cmd_list, str);
// 	if (str == NULL || new == NULL)
// 		errors(data, MALLOC_ERROR, 1);
//     expand_tonode(data, new, line);
// 	eputf("content: %s\n", new->content);
// 	eputf("value: %d\n", old_s - data->line);
//     str = ft_substr(data->line, 0, old_s - data->line);
// 	eputf("str: %s\n", str);
// 	str = ft_strjoin_fc(str, new->content, 3);
// 	eputf("str: %s\n", str);
// 	str = ft_strjoin_fc(str, *line, 1);
// 	eputf("str: %s\n", str);
// 	free(data->line);
// 	data->line = str;
// 	eputf("line: %s\n", data->line);
// }
