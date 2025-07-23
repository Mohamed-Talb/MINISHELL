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

static char  *check_cases(t_data *data, char **line)
{
	char *exvalue;
    char *s;

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
		return (free(exvalue), NULL);
    *line = s;
	return (exvalue);
}

char *regular_expand(t_data *data, char **line)
{
	char *env_var;
	char *token;
	char *s;

	token = check_cases(data, line);
	if (token != NULL)
		return (token);
	s = *line + 1;
	env_var = ft_strdup("");
	while (ft_isalnum(*s) || *s == '_')
		env_var = fappend(env_var, *s++);
	token = ft_strjoin_es(token, ft_getenv(data->exported, env_var), 0);
	*line = s;
	return (token);
}

int expand(t_data *data, char **line)  ///??????????????????????????????????????????????????
{
	int old_pos;
	char *chunk1;
	char *exvalue;
	char *chunk2;

	old_pos = *line - data->line;
	chunk1 = ft_substr(data->line, 0, old_pos);
	exvalue = regular_expand(data, line);
	chunk2 = ft_substr(*line, 0, ft_strlen(*line));
	free(data->line);
	data->line = mprintf("%f%f%f", chunk1, exvalue, chunk2);
	*line = data->line + old_pos;
	data->expand_rage = *line + ft_strlen(exvalue);
	return (0);
}
