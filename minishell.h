/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:54:30 by mtaleb            #+#    #+#             */
/*   Updated: 2025/08/06 23:10:19 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "macros.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				type;
	char			*error;
}					t_list;

typedef struct s_cmds
{
	int				inpipe[2];
	int				outpipe[2];
	int				found;
	int				permission;
	t_list			*allred;
	char			**flags;
	char			*cmd;
	char			*error;
}					t_cmds;

typedef struct s_data
{
	char			*line;
	char			**env;
	char			**exported;
	char			*expand_rage;
	int				pipes_nb;
	int				exit_code;
	t_cmds			**cmds;
	t_list			*cmd_list;
}					t_data;

int					parent(t_data *data);
void				grammer(t_data *data);
void				check(t_data *data, t_cmds *command);
int					child(t_data *data, t_cmds *command);

//  LIST UTILS
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstclear(t_list **Head);
t_list				*ft_lstprevlast(t_list *lst);
void				duplication(t_data *data, t_cmds *cmd);
t_list				*ft_lstback(t_list **head, void *content);

// MANAGE DATA
int					init_cmds(t_data *data);
t_data				*init_data(char **penv);
void				reset_data(t_data *data);

// UTILES
int					isdirectory(char *path);
int					exitestatus(int status);
t_list				*creat_node(t_data *data);
int					eputf(char *s, char **args);
char				*mprintf(char *s, char **args);
void				errors(char *error, int exitcode);
char				*unexpected_redirect(char **line);
void				set_errors(t_data *data, char *error, int exitcode);

// PARSING
t_list				*handle_arg(t_data *data, char **line);
int					parser(t_data *data, char *line, int cmd_count);
char				*expand(t_data *data, char *start, char **line);
t_list				*hpipe(t_data *data, t_list *token, char **line);
char				*single_q(t_data *data, char *token, char **line);
char				*double_q(t_data *data, char *token, char **start,
						char **line);
char				*get_enclosed_text(char *token, char **line);
char				*geth_enclosed_text(char *token, char **line);

// SIGNALS
void				signals(void);
int					signal_state(int state);
// BUILT-INS
int					check_builtin(char *cmd);
void				builtin(t_data *data, t_cmds *command);
int					ft_cd(int argc, char **argv, t_data *data);
int					ft_pwd(int argc, char **argv, t_data *data);
int					ft_env(int argc, char **argv, t_data *data);
int					ft_exit(int argc, char **argv, t_data *data);
int					ft_echo(int argc, char **argv, t_data *data);
int					ft_unset(int argc, char **argv, t_data *data);
int					ft_export(int argc, char **argv, t_data *data);

// EXPORT UTILES
int					vhasvalue(char *var);
int					isvalid_var(char *var);
int					varname_size(char *var);
void				sync_envs(t_data *data);
char				**envup(char **env, char *var);
char				**envrm(char **env, char *var);
char				*rgetenv(char **env, char *var);
char				*ft_getenv(char **env, char *var);
int					issame_var(char *str1, char *str2);
t_list				*redirection(t_data *data, t_list *token, char **line);

// HERDOC
t_data				**get_data(void);
char				*getdelemiter(char *s);
int					openallherdocs(t_data *data);
char				*get_expanded_line(t_data *data, char **line);
void				fill_herdoc(t_data *data, t_list *node, char *rname);

#endif