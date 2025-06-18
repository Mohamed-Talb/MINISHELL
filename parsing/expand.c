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

void expand(t_data *data, t_list *token, char **line, int mode)
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
	result = getenv(env_var);
	if (result == NULL || ft_strlen(token->content) == 0)
	{
		if (ft_strlen(token->content) != 0 || mode == 3)
			token->content = ft_strjoin_fc(token->content, "", 1);
		else
			token->content = ft_strjoin_fc(token->content, result, 1);
	}
	free(env_var);
	*line = s;
}
