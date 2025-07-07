# PIPEX SOURCE FILES
SHELL_SRC = \
	minishell.c \
	grammere/grammer.c \
	heredoc/herdocs.c heredoc/heredoc_utils.c \
	execution/child.c execution/check.c execution/parent.c \
	duplication/dupeexpand.c duplication/duplication.c duplication/openredfiles.c \
	env_tools/ft_getenv.c env_tools/shlvl.c env_tools/syncenvs.c env_tools/env_utils.c \
	parsing/parsing.c parsing/pipe.c parsing/expand.c parsing/qoutes.c parsing/redirection.c \
	helpers/cleanup.c helpers/signals.c helpers/lst_utils.c helpers/structs_utils.c helpers/utils.c \
	builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c builtin/builtin_management.c builtin/builtin_utils.c builtin/cd.c \

SHELL_OBJ = $(SHELL_SRC:.c=.o)

# COMPILER & FLAGS
CC = cc -g3
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# OUTPUT EXECUTABLE
NAME = minishell
LIBFT_DIR = libft
LIBFT_SRC = $(shell find $(LIBFT_DIR) -name '*.c' )
LIBFT = $(LIBFT_DIR)/libft.a # should this be named NAME1 or something..?

# RULES
all: $(NAME)

$(NAME): $(SHELL_OBJ) $(LIBFT)
	@$(CC) $(SHELL_OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) $(LDFLAGS)

$(LIBFT): $(LIBFT_SRC)
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

re: fclean all

.PHONY: all clean fclean re