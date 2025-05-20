
#include "pipex.h"

static t_list	*initbacknode(t_list **Head)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	if (!ft_lstaddback(Head, str))
		return (NULL);
	return (*Head);
}

static void	handlequotes(t_list *head, char *av, int *i, int *ps)
{
	t_list	*lst;

	if ((av[*i] == 34 || av[*i] == 39) && (*ps < 2 || *ps == av[*i]))
		*ps = ((*ps == av[*i]) * 1 + (*ps != av[*i]) * av[*i]);
	else
	{
		lst = ft_lstlast(head);
		lst->content = ft_append(lst->content, av[*i], -1);
	}
}

char	**getargs(char *av)
{
	t_list	*head;
	char	**ptr;

	int (ps), (i);
	(1) && (head = NULL, i = 0, ps = 0);
	while (av[i])
	{
		if (ft_iswhitespace(av[i]) && ps < 2)
			ps = 0;
		else
		{
			if (ps == 0)
			{
				if (!initbacknode(&head))
					return (NULL);
				ps = 1;
			}
			handlequotes(head, av, &i, &ps);
		}
		i++;
	}
	ptr = ft_lsttostr2(head);
	if (!ptr)
		return (NULL);
	return (ft_lstclear(&head), ptr);
}
