char  *herdoc_expand(t_data *data, char *line)
{
	int i = 0;
	char *var = NULL;
	char *result = ft_strdup("");
	char *varvalue = NULL;
	if (line == NULL)
		return NULL;
	while(line[i]  != '$')
	{
		result = ft_append(result, line[i], -1);
		i++;
	}
	i++;
	if (line[i] == '?')
	{
		result = ft_append(line, data->last_exit_status, -1);
		i++;
	}
	else if (ft_isdigit(line[i]) || line[i] == '\0' || ft_iswhitespace(line[i]))
	{
		result = ft_append(result, '$', -1);
		return (result);
	}
	else if (line[i] == '\'' || line[i] == '\"')
	{
		return (result);
	}
	else
	{
		while (ft_isalnum(line[i]) || line[i] == '_')
		{
			var = ft_append(var, line[i], -1);
			i++;
		}
		if (var == NULL)
		{
			result = ft_append(result, '$', -1);
			i++;
			return (result);
		}
		varvalue = getenv(var);
		result = ft_strjoin_fc(result, varvalue, 1);
		free(var);
	}
	free(line);
	line = NULL;
	return (result);
}