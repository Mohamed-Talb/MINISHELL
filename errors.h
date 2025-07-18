// ERRORS
#define REDIRECTION_SET "<|>"
#define PER_ERROR    "Permission denied"
#define CMD_NOTFOUND "command not found"
#define MALLOC_ERROR  "memory allocation faild"
#define UNEXPECTED_TOKEN  "minishell: syntax error near unexpected token `"
#define GETCWD_ERR "error retrieving current directory: getcwd: cannot access parent directories"

// types macros
#define CMD 1
#define PIPE 2
#define LEFT_RED 3
#define LEFT_HER 5
#define RIGHT_RED 4
#define RIGHT_HER 6

// BUILTIN-DEFINES:
// exit:
#define NUMREQ_CODE 256
#define EXCESS_ARGS_ERR "minishell: exit: too many arguments\n"
#define NUMREQ_ERR "minishell: exit: %s: numeric argument required\n"
// export:
#define AMBIGOUS_RED "minishell: %s: ambiguous redirect\n"
#define INVALID_IDERR "minishell: export: `%s': not a valid identifier\n"


#define CMD_NOT_FOUND "%s: command not found\n"
#define PERMISSIONS_DENIED "minishell: %s: Permission denied\n"
#define NO_SUCH_F_D "minishell: %s: No such file or directory\n"