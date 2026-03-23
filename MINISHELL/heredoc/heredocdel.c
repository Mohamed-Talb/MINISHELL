/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 09:32:34 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/28 09:32:57 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*expand_delemiter(char *token, char **line)
{
	char	*s;

	s = *line + 1;
	if (*s == '\0')
		token = fappend(token, '$');
	else if (*s == '\'' || *s == '"')
		token = geth_enclosed_text(token, &s);
	else
	{
		token = fappend(token, '$');
		token = fappend(token, *s++);
	}
	*line = s;
	return (token);
}

char	*getdelemiter(char *s)
{
	char	*ret;

	ret = ft_strdup("");
	while (*s != '\0' && ft_iswhitespace(*s) == false)
	{
		if (*s == '\'' || *s == '"')
			ret = geth_enclosed_text(ret, &s);
		else if (*s == '$')
			ret = expand_delemiter(ret, &s);
		else
			ret = fappend(ret, *s++);
	}
	return (ret);
}
