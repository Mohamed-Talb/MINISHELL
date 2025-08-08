#MINISHELL SRC
SHELL_SRC = \
	minishell.c \
	grammere/grammer.c \
	duplication/duplication.c \
	execution/child.c execution/check.c execution/parent.c \
	heredoc/heredocs.c heredoc/heredocdel.c heredoc/fillherdoc.c \
	env_tools/ft_getenv.c env_tools/syncenvs.c env_tools/env_utils.c \
	parsing/parsing.c parsing/pipe.c parsing/expand.c parsing/qoutes.c parsing/redirection.c \
	builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c builtin/builtin_management.c builtin/cd.c \
	helpers/cleanup.c helpers/signals.c helpers/lst_utils.c helpers/structs_utils.c helpers/utils.c helpers/exitstatus.c helpers/print_utils.c

SHELL_OBJ = $(SHELL_SRC:.c=.o)

# COMPILER & FLAGS
CC = cc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# OUTPUT EXECUTABLE
NAME = minishell

# LIBFT SRCS
LIBFT_DIR = libft/
LIBFT_SRC = $(addprefix $(LIBFT_DIR), \
	ft_cleaner/cleaner_utiles.c ft_fd/ft_putchar_fd.c ft_fd/ft_putendl_fd.c ft_fd/ft_putnbr_fd.c \
	ft_fd/ft_putstr_fd.c ft_is/ft_isalnum.c ft_is/ft_isalpha.c ft_is/ft_isascii.c ft_is/ft_isdigit.c \
	ft_is/ft_isprint.c ft_is/ft_iswhitespace.c ft_memory/ft_memchr.c ft_memory/ft_memcmp.c ft_memory/ft_memcpy.c \
	ft_memory/ft_memmove.c ft_memory/ft_memset.c ft_others/ft_close.c ft_others/ft_malloc.c ft_strings/ft_append.c \
	ft_strings/ft_append2.c ft_strings/ft_atoi.c ft_strings/ft_bzero.c ft_strings/ft_calloc.c ft_strings/ft_freedouble.c \
	ft_strings/ft_itoa.c ft_strings/ft_printdouble.c ft_strings/ft_putchar.c ft_strings/ft_putstr.c ft_strings/ft_remove.c \
	ft_strings/ft_remove2.c ft_strings/ft_set.c ft_strings/ft_split.c ft_strings/ft_strchr.c ft_strings/ft_strcmp.c \
	ft_strings/ft_strdup.c ft_strings/ft_strdup2.c ft_strings/ft_striteri.c ft_strings/ft_strjoin.c ft_strings/ft_strlcat.c \
	ft_strings/ft_strlcpy.c ft_strings/ft_strlen.c ft_strings/ft_strlen2.c ft_strings/ft_strmapi.c ft_strings/ft_strncmp.c \
	ft_strings/ft_strnstr.c ft_strings/ft_strrchr.c ft_strings/ft_strtrim.c ft_strings/ft_substr.c ft_strings/ft_tolower.c \
	ft_strings/ft_toupper.c ft_strings/ft_uitoa.c )

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

# RULES
all: $(NAME)

$(NAME): $(SHELL_OBJ) $(LIBFT_OBJ)
	@$(CC) $(SHELL_OBJ) $(LIBFT_OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(SHELL_OBJ) $(LIBFT_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re