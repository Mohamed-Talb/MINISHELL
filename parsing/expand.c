#include "../minishell.h"

int	expand(t_data *data, t_list *token, char *s, int i)
{
	char *env_var;
	char *result;

	env_var = NULL;
	if (s[i] == '$')
		i++;
	if (s[i] == '\0' || ft_iswhitespace(s[i]) == true)
	{
		token->content = ft_append(token->content, '$', -1);
		return (i);
	}
	else if (s[i] == '?')
	{
		token->content = ft_strjoin_fc(token->content, ft_itoa(data->last_exit_status), 3);
		i++;
	}
	else if (s[i] == '$') // echo $H$$$ is weird
	{
		token->content = ft_strjoin_fc(token->content, "$$", 1);
		return (i + 1);
	}
	else if (s[i] == '\'' || s[i] == '"')
		return (i);
	else
	{
		env_var = ft_strdup(""); // temp solution to many expantion errors, starting with NULL is a pain
		while (ft_isalnum(s[i]) || s[i] == '_')
		{
			env_var = ft_append(env_var, s[i], -1);
			i++;
		}
		result = getenv(env_var);
		// if (result != NULL) // dont check result bec i need to init the content by null fo remove it later
		token->content = ft_strjoin_fc(token->content, result, 1);
		free(env_var);
	}
	return (i);
}
