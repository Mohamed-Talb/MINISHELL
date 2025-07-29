// ERRORS
#define MALLOC_ERROR "memory allocation failed"
#define CMD_NOTFOUND "command not found"
#define PER_ERROR "Permission denied"
#define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'\n"
#define REDIRECTION_SET "<|>"
#define UNCLOSED_ERROR "minishell: syntax error: unclosed quote\n"

// types macros
#define CMD 1
#define PIPE 2
#define LEFT_RED 3
#define RIGHT_RED 4
#define LEFT_HER 5
#define RIGHT_HER 6

// DUPLICATION
#define AMBIGOUS_RED "minishell: %s: ambiguous redirect\n"

// EXEC
#define CMD_NOT_FOUND "minishell: %s: command not found\n"
#define NO_SUCH_F_D "minishell: %s: no such file or directory\n"
#define PERMISSIONS_DENIED "minishell: %s: Permission denied\n"

// HEREDOC
#define HEREDOC_EOF "warning: here-document delimited by end-of-file (wanted `%s')\n"
#define HEREDOC_PROMPT ">>> " // maybe change this to ">"

// PROMPT
#define PROMPT_DEFAULT "minishell>>  " 

// "\001\e[1;96m\002[ minishell ]\001\e[0m\002 \001\e[1;92m\002>>\001\e[0m\002 "
#define PROMPT_ERR "minishell>>  " 
// "\001\e[1;96m\002[ minishell ]\001\e[0m\002 \001\e[38;5;246m\002%d\001\e[0m\002 \001\e[1;91m\002>>\001\e[0m\002 " // pretty sure escapes like \x7f are needed here too

// CHECK
#define IS_DIR "%s: Is a directory\n"
#define IS_NOT_DIR "minishell: %s: Is Not a directory\n"

/* BUILTIN-DEFINES: */
// cd
#define GETCWD_ERR "minishell: error retrieving current directory: getcwd:cannot access parent directories: %s\n"
#define ARG_ERROR "minishell: cd: too many arguments\n"
#define HOME_ERROR "minishell: cd: HOME not set\n"
// exit:
#define NUMREQ_ERR "minishell: exit: %s: numeric argument required\n"
#define EXCESS_ARGS_ERR "minishell: exit: too many arguments\n"
#define NUMREQ_CODE 256
// export:
#define INVALID_IDERR "minishell: export: `%s': not a valid identifier\n"