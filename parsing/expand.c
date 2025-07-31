/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <kel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:59:48 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/31 15:30:04 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_cases(t_data *data, char **line)
{
	char	*token;
	char	*s;

	s = *line + 1;
	token = ft_strdup("");
	if (*s == '?')
	{
		token = ft_strjoin_es(token, ft_itoa(data->exit_code), 3);
		s++;
	}
	else if (*s == '$')
		token = (s++, ft_strjoin_es(token, "$$", 1));
	else if (*s == '\'' || *s == '"' || ft_isalpha(*s) || *s == '_')
	{
		ft_free(token);
		token = NULL;
	}
	else if (isdigit(*s))
		s++;
	else if (!ft_isalpha(*s) && *s != '_')
		token = fappend(token, '$');
	*line = s;
	return (token);
}

char *getexvalue(t_data *data, char **line)
{
    char *env_value;
    char *env_var;
    char *token;
    char *s;

    token = check_cases(data, line);
    if (token != NULL)
        return token;
    s = *line;
	env_var = ft_strdup("");
	while (ft_isalnum(*s) || *s == '_')
	{
		env_var = fappend(env_var, *s);
		s++;
	}
	env_value = ft_getenv(data->exported, env_var);
	token = ft_strjoin_es(token, env_value, 0);
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
