# PIPEX SOURCE FILES
SHELL_SRC = \
	minishell.c \
	helpers/utils.c helpers/lst_utils.c helpers/structs_utils.c helpers/signals.c helpers/cleanup.c \
	parsing/expand.c parsing/qoutes.c parsing/pipe.c parsing/parsing.c parsing/redirection.c \
	grammere/grammer.c grammere/herdocs.c \
	execution/check.c execution/child.c execution/parent.c execution/duplication.c \
	builtin/echo.c builtin/cd.c builtin/pwd.c builtin/export.c builtin/unset.c builtin/env.c \
	builtin/builtin_management.c builtin/exit.c builtin/exportutiles.c helpers/envutils.c

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