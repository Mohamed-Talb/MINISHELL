NAME = libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror
SRC =	ft_fd/ft_putendl_fd.c \
		ft_is/ft_isalnum.c ft_is/ft_isalpha.c ft_is/ft_isascii.c \
		ft_is/ft_isdigit.c ft_is/ft_isprint.c ft_is/ft_iswhitespace.c \
		ft_fd/ft_putnbr_fd.c ft_fd/ft_putchar_fd.c ft_fd/ft_putstr_fd.c \
		ft_memory/ft_memcpy.c ft_memory/ft_memmove.c \
		ft_memory/ft_memcmp.c ft_memory/ft_memset.c ft_memory/ft_memchr.c \
		ft_strings/ft_strlcat.c ft_strings/ft_itoa.c ft_strings/ft_strdup2.c \
		ft_strings/ft_split.c ft_strings/ft_append.c ft_strings/ft_strlen2.c \
		ft_strings/ft_append2.c ft_strings/ft_substr.c ft_strings/ft_strchr.c \
		ft_strings/ft_strrchr.c ft_strings/ft_strlen.c ft_strings/ft_strlcpy.c \
		ft_strings/ft_tolower.c ft_strings/ft_toupper.c ft_strings/ft_calloc.c \
		ft_strings/ft_bzero.c ft_strings/ft_strdup.c \
		ft_strings/ft_striteri.c ft_strings/ft_strmapi.c ft_strings/ft_strnstr.c \
		ft_strings/ft_strjoin.c ft_strings/ft_strtrim.c ft_strings/ft_freedouble.c \
		ft_strings/ft_atoi.c ft_strings/ft_strcmp.c ft_strings/ft_strncmp.c ft_strings/ft_remove.c \
		ft_printf/printchar.c \
		ft_printf/flags.c ft_printf/ft_printf.c ft_printf/inits.c \
		ft_printf/utils.c ft_printf/checks.c ft_printf/precision.c \
		ft_printf/width.c ft_printf/printint.c ft_printf/printstring.c \
		ft_printf/printhexa.c ft_printf/printunsigned.c ft_printf/printmemory.c \
		ft_strings/ft_remove2.c ft_strings/ft_uitoa.c ft_others/ft_malloc.c ft_cleaner/cleaner_utiles.c \
		ft_cleaner/ft_cleaner.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: all clean fclean re