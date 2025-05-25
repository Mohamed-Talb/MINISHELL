#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>

// ERRORS
#define MALLOC_ERROR "memory allocation faild"
#define CMD_NOTFOUND "command not found"
#define PER_ERROR "Permission denied"
#define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `"
#define REDIRECTION_SET "<|>"


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

typedef struct s_cmds
{
	char **cmd;
	int pipein;
	int pipeout;
	t_dlist *allred;
} t_cmds;

typedef struct s_data
{
	char	*line;
	char	**env;
	int		last_exit_status;
	int 	pipes_nb;
	int 	index;
	t_dlist	*cmd_list;
	t_cmds	**cmds;
} t_data;


void	grammer(t_data *data);
void	printdoule(char **str);
void	executor(t_data *data);
void 	open_herdocs(t_data *data, t_dlist *node);
void	redir_setup(t_data *data);
char	*ft_strjoin_fc(char *str, char *buff, int choice);
void	check(t_data *data, t_cmds *command);
int	parent(t_data *data);
int	child(t_data *data, t_cmds *command);

// 2D LIST UTILS 
void	f(void *content);
int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
void	ft_dlstclear(t_dlist **Head);
int		duplication(t_data *data, t_cmds *cmd);
t_dlist	*ft_dlstback(t_dlist **head, void *content);
t_dlist	*ft_dlstfront(t_dlist **head, void *content);
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));

// MANAGE DATA
void	free_data(t_data *data);
int 	init_cmds(t_data *data);
int 	init_data(t_data *data, char **penv);

// UTILES
void 	errors(t_data *data, char *error, int exitcode);
int 	in_set(char *set, char c);
char 	*randomnbr();
// PARSING 
int		parser(t_data *data, char *line);
char	*expand(t_data *data, char *token, char **line);
int		hpipe(t_data *data, t_dlist *token, char **line);
char	*single_q(t_data *data, char *token, char **line);
void	redirect(t_data *data, t_dlist *token, char **line);
int		handle_arg(t_data *data, t_dlist *token, char **line);
int		double_q(t_data *data, t_dlist *token, char **line, int state);