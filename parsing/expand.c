/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:59:48 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/27 20:30:52 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_cases(t_data *data, char **line)
{
	char	*exvalue;
	char	*s;

	s = *line + 1;
	exvalue = ft_strdup("");
	if (*s == '?')
	{
		exvalue = ft_strjoin_es(exvalue, ft_itoa(data->exit_code), 3);
		s++;
	}
	else if (*s == '$')
	{
		exvalue = ft_strjoin_es(exvalue, "$$", 1);
		s++;
	}
	else if (*s == '\0' || ft_iswhitespace(*s))
		exvalue = fappend(exvalue, '$');
	else if (ft_isdigit(*s))
		s++;
	else if (*s != '\'' && *s != '"')
		return (ft_free(exvalue), NULL);
	*line = s;
	return (exvalue);
}

char	*getexvalue(t_data *data, char **line)
{
	char	*env_value;
	char	*env_var;
	char	*token;
	char	*s;

	token = check_cases(data, line);
	if (token != NULL)
		return (token);
	s = *line + 1;
	env_var = ft_strdup("");
	while (ft_isalnum(*s) || *s == '_')
	{
		env_var = fappend(env_var, *s);
		s++;
	}
	env_value = ft_getenv(data->exported, env_var);
	token = ft_strjoin_es(token, env_value, 2);
	*line = s;
	return (token);
}

char	*expand(t_data *data, char *start, char **line)
{
	int		old_pos;
	char	*chunk1;
	char	*exvalue;
	char	*chunk2;
	int		len;

	old_pos = *line - start;
	chunk1 = ft_substr(start, 0, old_pos);
	exvalue = getexvalue(data, line);
	chunk2 = ft_substr(*line, 0, ft_strlen(*line));
	len = ft_strlen(exvalue);
	ft_free(start);
	start = mprintf("%s%s%s", chunk1, exvalue, chunk2);
	*line = start + old_pos;
	data->expand_rage = *line + len;
	ft_free(chunk1);
	ft_free(chunk2);
	ft_free(exvalue);
	return (start);
}
