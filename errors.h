
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

// BUILTIN-DEFINES:

// cd 
#define GETCWD_ERR "minishell: error retrieving current directory: getcwd: cannot access parent directories: %s\n"
#define ARG_ERROR "minishell: cd: too many arguments\n"
#define HOME_ERROR "minishell: cd: HOME not set\n"
// exit:
#define NUMREQ_ERR "minishell: exit: %s: numeric argument required\n"
#define EXCESS_ARGS_ERR "minishell: exit: too many arguments\n"
#define NUMREQ_CODE 256
// export:
#define INVALID_IDERR "minishell: export: `%s': not a valid identifier\n"

#define AMBIGOUS_RED "minishell: %s: ambiguous redirect\n"

#define CMD_NOT_FOUND "minishell: %s: command not found\n"
#define NO_SUCH_F_D "minishell: %s: no such file or directory\n"
#define PERMISSIONS_DENIED "minishell: %s: Permission denied\n"