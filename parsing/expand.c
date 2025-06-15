#include "../minishell.h"

int	expand(t_data *data, t_dlist *token, char *s, int i)
{
	char *env_var;
	char *result;

	env_var = NULL;
	if (s[i] == '$')
		i++;
	if (s[i] == '?')
	{
		token->content = ft_strjoin_fc(token->content, ft_itoa(data->last_exit_status), 3);
		i++;
	}
	else if (s[i] == '\0' || ft_iswhitespace(s[i]) == true)
	{
		token->content = ft_append(token->content, '$', -1);
		return (i);
	}
	else if (s[i] == '\'' || s[i] == '"')
		return (i);
	else
	{
		while (ft_isalnum(s[i]) || s[i] == '_')
		{
			env_var = ft_append(env_var, s[i], -1);
			i++;
		}
		if (env_var == NULL) // echo $H$$$ is weird
		{
			token->content = ft_strjoin_fc(token->content, "$$", 1);
			return (i + 1);
		}
		result = getenv(env_var);
		if (result != NULL)
			token->content = ft_strjoin_fc(token->content, result, 1);
		free(env_var);
	}
	return (i);
}
