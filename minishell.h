#define _POSIX_SOURCE
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
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
// ERRORS
#define MALLOC_ERROR "memory allocation faild"
#define CMD_NOTFOUND "command not found"
#define PER_ERROR "Permission denied"
#define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `"
#define REDIRECTION_SET "<|>"
#define GETCWD_ERR "error retrieving current directory: getcwd: cannot access parent directories"

// types macros
#define CMD 1
#define PIPE 2
#define LEFT_RED 3
#define RIGHT_RED 4
#define LEFT_HER 5
#define RIGHT_HER 6



typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				type;
	char 			*error;
}	t_list;

typedef struct s_cmds
{
	char *cmd;
	char **flags;
	int pipein;
	int pipeout;
	t_list *allred;
} t_cmds;

typedef struct s_data
{
	char	*line;
	char	**env;
	int		last_exit_status;
	int 	pipes_nb;
	char	**exported;
	int		command_count;
	t_list	*cmd_list;
	t_cmds	**cmds;
} t_data;

void	grammer(t_data *data);
void	printdoule(char **str);
char 	**envup(char **env, char *newvar);
void 	open_herdocs(t_data *data, t_list *node);
char	*ft_strjoin_fc(char *str, char *buff, int choice);
char	*ft_strjoin_es(char *str, char *buff, int choice);
void	check(t_data *data, t_cmds *command);
int		parent(t_data *data);
int		child(t_data *data, t_cmds *command);

//  LIST UTILS 
void	f(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstprevlast(t_list *lst);
void	ft_lstclear(t_list **Head);
int		duplication(t_data *data, t_cmds *cmd);
t_list	*ft_lstback(t_list **head, void *content);
t_list	*ft_lstfront(t_list **head, void *content);
void	ft_lstiter(t_list *lst, void (*f)(void *));

// MANAGE DATA
void	free_data(t_data *data);
void	reset_data(t_data *data);
int 	init_cmds(t_data *data);
t_data	*init_data(char **penv);

// UTILES
char 	*randomnbr();
void	print_cmds(t_data *data);
int 	in_set(char *set, char c);
int		posin_set(char *set, char c);
void 	errors(t_data *data, char *error, int exitcode);
void 	set_errors(t_data *data, char *error, int exitcode);
void	errcln(t_data *data, int exitcode, char *error, ...);

// PARSING 
int		parser(t_data *data, char *line);
char	*expand(t_data *data, char **line);
int		hpipe(t_data *data, t_list *token, char **line);
void	single_q(t_data *data, t_list *token, char **line);
void	redirection(t_data *data, t_list *token, char **line);
void	double_q(t_data *data, t_list *token, char **line, int state);

//SIGNALS 
void 	signals(int mode);

// BUILT-INS
int		check_builtin(char *cmd);
void	execute_builtin(t_data *data, t_cmds *command);
int 	ft_echo(int argc, char **argv, t_data *data);
int		ft_cd(int argc, char **argv, t_data *data);
int		ft_pwd(int argc, char **argv, t_data *data);
int		ft_export(int argc, char **argv, t_data *data);
int		ft_unset(int argc, char **argv, t_data *data);
int		ft_env(int argc, char **argv, t_data *data);
int		ft_exit(int argc, char **argv, t_data *data);


// EXPORT UTILES
int checkdups(char **variables, char *target);
int issame_var(char *str1, char *str2);
void print_exported(char **exported);
void print_variable(char *var);


int ftup_env(t_data *data, char ***env, char *newvar);
int getenvpos(char **env, char *var);
char *dupexpand(t_data *data, char **line);
char *herexpand(t_data *data, char **line);
void openredfiles(t_data *data, t_list *node);