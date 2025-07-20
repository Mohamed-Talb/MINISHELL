/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:39:35 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/20 14:39:36 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_cases(t_data *data, char **token, char *s, int *i)
{
	if (s[*i] == '\0' || ft_iswhitespace(s[*i]) || s[*i] == '\'' 
			|| s[*i] == '"')
	{
		*token = ft_append(*token, '$', -1);
		return (1);
	}
	else if (s[*i] == '?')
	{
		char *status = ft_itoa(data->last_exit_status);
		*token = ft_strjoin_fc(*token, status, 3);
		(*i)++;
		return (1);
	}
	else if (s[*i] == '$')
	{
		*token = ft_strjoin_fc(*token, "$$", 1);
		(*i)++;
		return (1);
	}
	return (0);
}

static int get_exp_value(t_data *data, char **token, char *s)
{
	char *env_var = NULL;
	char *result = NULL;
	int i;

	i = 1;
	if (check_cases(data, token, s, &i))
		return (i);
	env_var = ft_strdup("");
	while (ft_isalnum(s[i]) || s[i] == '_')
	{
		env_var = ft_append(env_var, s[i], -1);
		i++;
	}
	if (env_var[0] == 0)
	{
		*token = fappend(*token, '$');
		return (i);
	}
	result = ft_getenv(data->exported, env_var);
	*token = ft_strjoin_es(*token, result, 1);
	return (i);
}

int expand(t_data *data, char **line)  ///??????????????????????????????????????????????????
{
	int i;
	int pos;
	char *str;
	int old_size;
	int expand_size;

	pos = *line - data->line;
	str = ft_substr(data->line, 0, pos);
	old_size = ft_strlen(str);
	i = get_exp_value(data, &str, *line);
	expand_size = ft_strlen(str) - old_size;
	data->line = ft_strjoin_fc(str, *line + i, 1);
	*line = data->line + pos;
	data->expand_rage = *line + expand_size;
	return (expand_size);
}
