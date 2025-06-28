#include "../minishell.h"

int upoldpwd(t_data *data)
{
	char *new;

	new = ft_getenv(data->exported, "PWD");
	if (new == NULL)
		data->exported = envup(data->exported, "OLDPWD"); // this is needed when PWD is unset before a cd
	else
	{
		new = ft_strjoin("OLDPWD=", new);
		data->exported = envup(data->exported, new);
		free(new);
	}
	if (!data->exported)
		return (1);
	return (0);
}

int uppwd(t_data *data, char *path)
{
	char buff[999999];
	char *new;

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		eputf("cd: %s: %s\n", GETCWD_ERR, strerror(errno));
		new = ft_getenv(data->exported, "PWD");
		new = append(new - 4, '/');
		new = ft_strjoin_fc(new, path, 1);
	}
	else
		new = ft_strjoin("PWD=", buff);
	if (new == NULL)
		return(eputf(MALLOC_ERROR), 1);
	data->exported = envup(data->exported, new);
	if (!data->exported)
		return (1);
	return (0);
}

char *ascii_order(char **arr)
{
    int i;
    char *prev;

    i = 0;
    prev = arr[0];
    while (arr[i] != NULL)
    {
        if (ft_strcmp(prev, arr[i]) < 0)
            prev = arr[i];
        i++;
    }
    return (prev);
}

void print_variable(char *var)
{
    while (*var)
    {
        ft_putchar(*var);
        if (*var == '=')
        {
            ft_printf("\"%s\"\n", var + 1);
            return ;
        }
        var++;
    }
    ft_putchar('\n');
}

void print_exported(char **exported)
{
    char *prev;
    char *curr;
    int i;
    int j;

    j = ft_strlen2(exported);
    prev = NULL;
    while (j > 0)
    {
        i = 0;
        curr = ascii_order(exported);
        while (exported[i])
        {
            if (ft_strcmp(curr, exported[i]) > 0 && (prev == NULL || ft_strcmp(prev, exported[i]) < 0))
                curr = exported[i];
            i++;
        }
        prev = curr;
        print_variable(prev);
        j--;
    }
}
