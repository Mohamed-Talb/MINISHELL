#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include <readline/history.h>

// ERRORS
#define MALLOC_ERROR "emory allocation faild"
#define CMD_NOTFOUND "command not found"
#define PER_ERROR "Permission denied"

// types macros
#define CMD 1
#define PIPE 2
#define LEFT_RED 3
#define RIGHT_RED 4
#define LEFT_HER 5
#define RIGHT_HER 6

typedef struct s_dlist
{
	int				type;
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_data
{
	char	*line;
	char    **env;
	// char 	**env;
	int		last_exit_status;
	t_dlist	*cmd_list;
} t_data;

// double linked list utils
void	errors(t_data *data, char *error);
int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
void	ft_dlstclear(t_dlist **Head);
t_dlist	*ft_dlstback(t_dlist **head, void *content);
t_dlist	*ft_dlstfront(t_dlist **head, void *content);
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
void 	f(void *content);
int in_set(char *set, char c);
int 	init_data(t_data *data);
void	free_data(t_data *data);
int		parser(t_data *data, char *line);
char	*ft_strjoin_fc(char *str, char *buff, int choice);

// PARSING 
char *expand(t_data *data, char *token, char **line);
int handle_arg(t_data *data, t_dlist *token, char **line);
int parser(t_data *data, char *line);
int hpipe(t_data *data, t_dlist *token, char **line);
char *single_q(t_data *data, char *token, char **line);
int double_q(t_data *data, t_dlist *token, char **line, int state);
void redirect(t_data *data, t_dlist *token, char **line);