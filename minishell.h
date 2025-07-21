#ifndef MINISHELL_H
#define MINISHELL_H

// #define _POSIX_SOURCE
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
#include "errors.h"

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
	int infd;
	int outfd;
	t_list *allred;
} t_cmds;

typedef struct s_data
{
	char	*line;
	char	**env;
	char	**exported;
	char	*expand_rage;
	int 	pipes_nb;
	int		command_count;
	int		last_exit_status;
	t_cmds	**cmds;
	t_list	*cmd_list;
} t_data;

void	grammer(t_data *data);
void	printdoule(char **str);
char	*ft_strjoin_fc(char *str, char *buff, int choice);
char	*ft_strjoin_es(char *str, char *buff, int choice);
void	check(t_data *data, t_cmds *command);
int		parent(t_data *data);
int		child(t_data *data, t_cmds *command);

//  LIST UTILS 
void	f(void *content);
int		ft_lstsize(t_list *lst);
t_list *ft_lstnew(void *content);
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
t_list *creat_node(t_data *data);
int		exitestatus(int status);
void	print_cmds(t_data *data);
int 	in_set(char *set, char c);
int		posin_set(char *set, char c);
void 	errors(t_data *data, char *error, int exitcode);
void 	set_errors(t_data *data, char *error, int exitcode);
void	errcln(t_data *data, int exitcode, char *error, ...);
char 	*mfor_printf(char *str, void *sarr[], int darr[]);

// PARSING 
int		parser(t_data *data, char *line);
int		expand(t_data *data, char **line);
t_list *handle_arg(t_data *data, char **line);
t_list	*hpipe(t_data *data, t_list *token, char **line);
void	single_q(t_data *data, t_list *token, char **line);
void redirection(t_data *data, t_list *token, char **line);
void	double_q(t_data *data, t_list *token, char **line, int state);

// SIGNALS 
void	signals();
int		signal_state(int state);
// BUILT-INS
int		check_builtin(char *cmd);
void	builtin(t_data *data, t_cmds *command);
int 	ft_echo(int argc, char **argv, t_data *data);
int		ft_cd(int argc, char **argv, t_data *data);
int		ft_pwd(int argc, char **argv, t_data *data);
int		ft_export(int argc, char **argv, t_data *data);
int		ft_unset(int argc, char **argv, t_data *data);
int		ft_env(int argc, char **argv, t_data *data);
int		ft_exit(int argc, char **argv, t_data *data);


// EXPORT UTILES
int issame_var(char *str1, char *str2);
int isvalid_var(char *var);
int getenvpos(char **env, char *var);
char *dupexpand(t_data *data, char **line);
int	openredfiles(t_data *data, t_list *node);
int varname_size(char *var);
char **envup(char **env, char *var);
char **envrm(char **env, char *var);
char **adjust_shell_level(char **env, int change);
void sync_envs(t_data *data);
char *ft_getenv(char **env, char *var);

// HERDOC
char 	*getdelemiter(t_data *data, char *s);
char	*getexline(t_data *data, char *line);
int		openallherdocs(t_data *data);
#endif