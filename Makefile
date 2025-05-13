# LIBFT SOURCE FILES
LIBFT_SRC = libft/ft_fd/ft_putendl_fd.c \
			libft/ft_is/ft_isalnum.c libft/ft_is/ft_isalpha.c libft/ft_is/ft_isascii.c \
			libft/ft_is/ft_isdigit.c libft/ft_is/ft_isprint.c libft/ft_is/ft_iswhitespace.c \
			libft/ft_fd/ft_putnbr_fd.c libft/ft_fd/ft_putchar_fd.c libft/ft_fd/ft_putstr_fd.c \
			libft/ft_memory/ft_memcpy.c libft/ft_memory/ft_memmove.c \
			libft/ft_memory/ft_memcmp.c libft/ft_memory/ft_memset.c libft/ft_memory/ft_memchr.c \
			libft/ft_linkedlist/ft_lstclear.c libft/ft_linkedlist/ft_lstaddfront.c \
			libft/ft_linkedlist/ft_lstsize.c libft/ft_linkedlist/ft_lstlast.c libft/ft_linkedlist/ft_lstnew.c \
			libft/ft_linkedlist/ft_lstaddback.c libft/ft_linkedlist/ft_lstiter.c libft/ft_linkedlist/ft_lstdelone.c \
			libft/ft_strings/ft_strlcat.c libft/ft_strings/ft_itoa.c libft/ft_strings/ft_strdup2.c \
			libft/ft_strings/ft_split.c libft/ft_strings/ft_append.c libft/ft_strings/ft_strlen2.c \
			libft/ft_strings/ft_append2.c libft/ft_strings/ft_substr.c libft/ft_strings/ft_strchr.c \
			libft/ft_strings/ft_strrchr.c libft/ft_strings/ft_strlen.c libft/ft_strings/ft_strlcpy.c \
			libft/ft_strings/ft_tolower.c libft/ft_strings/ft_toupper.c libft/ft_strings/ft_calloc.c \
			libft/ft_strings/ft_bzero.c libft/ft_strings/ft_strdup.c libft/ft_strings/ft_lsttostr2.c \
			libft/ft_strings/ft_striteri.c libft/ft_strings/ft_strmapi.c libft/ft_strings/ft_strnstr.c \
			libft/ft_strings/ft_strjoin.c libft/ft_strings/ft_strtrim.c libft/ft_strings/ft_freedouble.c \
			libft/ft_strings/ft_atoi.c libft/ft_strings/ft_strcmp.c libft/ft_strings/ft_strncmp.c libft/ft_strings/ft_remove.c \
			libft/ft_printf/printchar.c \
			libft/ft_printf/flags.c libft/ft_printf/ft_printf.c libft/ft_printf/inits.c \
			libft/ft_printf/utils.c libft/ft_printf/checks.c libft/ft_printf/precision.c \
			libft/ft_printf/width.c libft/ft_printf/printint.c libft/ft_printf/printstring.c \
			libft/ft_printf/printhexa.c libft/ft_printf/printunsigned.c libft/ft_printf/printmemory.c \
			libft/ft_others/ft_getnextline.c
	
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

# PIPEX SOURCE FILES
SHELL_SRC = minishell.c utils.c cleanup.c double_lst.c envutils.c\
			parsing/expand.c parsing/qoutes.c parsing/pipe.c parsing/parsing.c\
			parsing/redirection.c
			
SHELL_OBJ = $(SHELL_SRC:.c=.o)

# COMPILER & FLAGS
CC = cc -g3
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# OUTPUT EXECUTABLE
NAME = minishell

# RULES
all: $(NAME)

$(NAME): $(SHELL_OBJ) $(LIBFT_OBJ)
	@$(CC) $(SHELL_OBJ) $(LIBFT_OBJ) -o $(NAME) $(LDFLAGS)


# COMPILE OBJECTS
# libft/%.o: libft/%.c
# 	@$(CC) $(FLAGS) -c $< -o $@
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(SHELL_OBJ) $(LIBFT_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re