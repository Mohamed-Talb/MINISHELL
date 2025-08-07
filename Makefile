
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
LIBFT_DIR = libft
LIBFT_SRC = \
	libft/ft_cleaner/cleaner_utiles.c libft/ft_fd/ft_putchar_fd.c libft/ft_fd/ft_putendl_fd.c libft/ft_fd/ft_putnbr_fd.c \
	libft/ft_fd/ft_putstr_fd.c libft/ft_is/ft_isalnum.c libft/ft_is/ft_isalpha.c libft/ft_is/ft_isascii.c libft/ft_is/ft_isdigit.c \
	libft/ft_is/ft_isprint.c libft/ft_is/ft_iswhitespace.c libft/ft_memory/ft_memchr.c libft/ft_memory/ft_memcmp.c libft/ft_memory/ft_memcpy.c \
	libft/ft_memory/ft_memmove.c libft/ft_memory/ft_memset.c libft/ft_others/ft_close.c libft/ft_others/ft_malloc.c libft/ft_strings/ft_append.c \
	libft/ft_strings/ft_append2.c libft/ft_strings/ft_atoi.c libft/ft_strings/ft_bzero.c libft/ft_strings/ft_calloc.c libft/ft_strings/ft_freedouble.c \
	libft/ft_strings/ft_itoa.c libft/ft_strings/ft_printdouble.c libft/ft_strings/ft_putchar.c libft/ft_strings/ft_putstr.c libft/ft_strings/ft_remove.c \
	libft/ft_strings/ft_remove2.c libft/ft_strings/ft_set.c libft/ft_strings/ft_split.c libft/ft_strings/ft_strchr.c libft/ft_strings/ft_strcmp.c \
	libft/ft_strings/ft_strdup.c libft/ft_strings/ft_strdup2.c libft/ft_strings/ft_striteri.c libft/ft_strings/ft_strjoin.c libft/ft_strings/ft_strlcat.c \
	libft/ft_strings/ft_strlcpy.c libft/ft_strings/ft_strlen.c libft/ft_strings/ft_strlen2.c libft/ft_strings/ft_strmapi.c libft/ft_strings/ft_strncmp.c \
	libft/ft_strings/ft_strnstr.c libft/ft_strings/ft_strrchr.c libft/ft_strings/ft_strtrim.c libft/ft_strings/ft_substr.c libft/ft_strings/ft_tolower.c \
	libft/ft_strings/ft_toupper.c libft/ft_strings/ft_uitoa.c

NAME_1 = $(LIBFT_DIR)/libft.a

# RULES
all: $(NAME)

$(NAME): $(SHELL_OBJ) $(NAME_1)
	@$(CC) $(SHELL_OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) $(LDFLAGS)

$(NAME_1): $(LIBFT_SRC)
	@make -s -C $(LIBFT_DIR) 

cleanup:
	@rm -f $(SHELL_OBJ)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(SHELL_OBJ)
	@make -s -C $(LIBFT_DIR) clean 

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT_DIR) fclean 

re: fclean all

.PHONY: all clean fclean re