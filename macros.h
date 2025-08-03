/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:26:14 by kel-mous          #+#    #+#             */
/*   Updated: 2025/08/03 21:54:50 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

// ERRORS
# define REDIRECTION_SET "<|>"
# define PER_ERROR "Permission denied"
# define CMD_NOTFOUND "command not found"
# define MALLOC_ERROR "memory allocation failed"
# define UNCLOSED_ERROR "minishell: syntax error: unclosed quote\n"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'\n"

// types macros
# define CMD 1
# define PIPE 2
# define LEFT_RED 3
# define RIGHT_RED 4
# define LEFT_HER 5
# define RIGHT_HER 6

// ANSI CODE
# define RESET "\001\e[0m\002"
# define CYAN "\001\e[1;96m\002"
# define GREEN "\001\e[1;92m\002"

// DUPLICATION
# define AMBIGOUS_RED "minishell: %s: ambiguous redirect\n"

// EXEC
# define CMD_NOT_FOUND "minishell: %s: command not found\n"
# define PERMISSIONS_DENIED "minishell: %s: Permission denied\n"
# define NO_SUCH_F_D "minishell: %s: no such file or directory\n"

// HEREDOC 
# define HEREDOC_PROMPT "> " 
# define HEREDOC_EOF  "warning: here-document delimited by end-of-file"

// CHECK
# define IS_DIR "minishell: %s: Is a directory\n"
# define IS_NOT_DIR "minishell: %s: Is Not a directory\n"

//BUILTIN-DEFINES
// cd
# define HOME_ERROR "minishell: cd: HOME not set\n"
# define GCWD_ER_P "error retrieving current directory"
# define ARG_ERROR "minishell: %s: too many arguments\n"
# define GCWD_ER_S "getcwd: cannot access parent directories"

// exit:
# define NUMREQ_CODE 256
# define EXCESS_ARGS_ERR "minishell: exit: too many arguments\n"
# define NUMREQ_ERR "minishell: exit: %s: numeric argument required\n"

// export:
# define INVALID_IDERR "minishell: export: `%s': not a valid identifier\n"

#endif
