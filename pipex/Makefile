
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
			libft/ft_strings/ft_atoi.c libft/ft_strings/ft_strcmp.c libft/ft_strings/ft_strncmp.c \
			libft/ft_strings/ft_strlcat.c libft/ft_strings/ft_itoa.c libft/ft_strings/ft_strdup2.c \
			libft/ft_strings/ft_split.c libft/ft_strings/ft_append.c libft/ft_strings/ft_strlen2.c \
			libft/ft_strings/ft_append2.c libft/ft_strings/ft_substr.c libft/ft_strings/ft_strchr.c \
			libft/ft_strings/ft_strrchr.c libft/ft_strings/ft_strlen.c libft/ft_strings/ft_strlcpy.c \
			libft/ft_strings/ft_tolower.c libft/ft_strings/ft_toupper.c libft/ft_strings/ft_calloc.c \
			libft/ft_strings/ft_bzero.c libft/ft_strings/ft_strdup.c libft/ft_strings/ft_lsttostr2.c \
			libft/ft_strings/ft_striteri.c libft/ft_strings/ft_strmapi.c libft/ft_strings/ft_strnstr.c \
			libft/ft_strings/ft_strjoin.c libft/ft_strings/ft_strtrim.c libft/ft_strings/ft_freedouble.c \
			libft/ft_printf/printchar.c \
			libft/ft_printf/flags.c libft/ft_printf/ft_printf.c libft/ft_printf/inits.c \
			libft/ft_printf/utils.c libft/ft_printf/checks.c libft/ft_printf/precision.c \
			libft/ft_printf/width.c libft/ft_printf/printint.c libft/ft_printf/printstring.c \
			libft/ft_printf/printhexa.c libft/ft_printf/printunsigned.c libft/ft_printf/printmemory.c \
			libft/ft_others/ft_getnextline.c
	
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)


# PIPEX SOURCE FILES
PIPEX_SRC = parcing.c utils.c check.c getargs.c child.c pipex.c
PIPEX_OBJ = $(PIPEX_SRC:.c=.o)

# PIPEX BONUS SOURCE FILES
PIPEXBONUS_SRC = parcing.c utils.c check.c getargs.c child.c heredoc.c pipexbonus.c
PIPEXBONUS_OBJ = $(PIPEXBONUS_SRC:.c=.o)


# COLORS
RESET = \033[0m
RED = \033[1;31m
BLUE = \033[1;34m
CYAN = \033[1;36m
BLACK = \033[1;30m
WHITE = \033[1;37m
GREEN = \033[1;32m
PURPLE = \033[1;35m

# Special characters
GEAR = ⚙️
CHECK = ✓
SPARK = ✨
ROCKET = 🚀

# COMPILER & FLAGS
CC = cc
FLAGS = -Wall -Wextra -Werror

# OUTPUT EXECUTABLE
NAME = pipex
BONUSNAME = pipex_bonus

# RULES
all: logo $(NAME)

bonus: $(BONUSNAME)

logo:
	@clear
	@echo "\n\n"
	@echo "$(CYAN)Loading ORION PIPE Engine...$(RESET)"
	@sleep 0.5
	@echo "$(CYAN)"
	@echo "   ██████╗  ██████╗  ██╗  ██████╗  ███╗   ██╗ "
	@sleep 0.1
	@echo "  ██╔═══██╗ ██╔══██╗ ██║ ██╔═══██╗ ████╗  ██║"
	@sleep 0.1
	@echo "  ██║   ██║ ██████╔╝ ██║ ██║   ██║ ██╔██╗ ██║"
	@sleep 0.1
	@echo "  ██║   ██║ ██╔══██╗ ██║ ██║   ██║ ██║╚██╗██║"
	@sleep 0.1
	@echo "  ╚██████╔╝ ██║  ██║ ██║ ╚██████╔╝ ██║ ╚████║"
	@sleep 0.1
	@echo "   ╚═════╝  ╚═╝  ╚═╝ ╚═╝  ╚═════╝  ╚═╝  ╚═══╝"
	@sleep 0.2
	@echo "$(CYAN)BY: mtaleb $(RESET)"
	@echo "\n$(CYAN)INITIALIZE ORION PIPEX COMPONENTS $(SPARK)$(RESET)"
	@sleep 0.5

$(NAME): $(PIPEX_OBJ) $(LIBFT_OBJ) $(PRINTF_OBJ)
	@echo "\n$(RED)$(GEAR) CREATING PIPEX PROGRAM...$(RESET)"
	@$(CC) $(PIPEX_OBJ) $(LIBFT_OBJ) -o $(NAME)
	@echo "$(GREEN)$(CHECK) BINARY COMPILATION COMPLETE$(RESET)"
	@echo "\n$(CYAN)PIPEX GENERATOR IS READY FOR LAUNCH 🚀$(RESET)\n"

$(BONUSNAME): $(PIPEXBONUS_OBJ) $(LIBFT_OBJ) $(PRINTF_OBJ)
	@echo "\n$(RED)$(GEAR) CREATING PIPEX BONUS PROGRAM...$(RESET)"
	@$(CC) $(PIPEXBONUS_OBJ) $(LIBFT_OBJ) -o $(BONUSNAME)
	@echo "$(GREEN)$(CHECK) BONUS BINARY COMPILATION COMPLETE$(RESET)"
	@echo "\n$(CYAN)PIPEX BONUS GENERATOR IS READY 🚀$(RESET)\n"

# COMPILE OBJECTS
libft/%.o: libft/%.c
	@echo "$(BLACK)$(GEAR) COMPILING $<...$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)$(CHECK) COMPILED $< SUCCESSFULLY$(RESET)"

%.o: %.c
	@echo "$(BLACK)$(GEAR) COMPILING $<...$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)$(CHECK) COMPILED $< SUCCESSFULLY$(RESET)"

clean:
	@rm -f $(PIPEX_OBJ) $(PIPEXBONUS_OBJ) $(LIBFT_OBJ)

fclean: clean
	@rm -f $(NAME) $(BONUSNAME)

re: fclean all

.SECONDARY: $(LIBFT_OBJ) $(PIPEX_OBJ) $(PIPEXBONUS_OBJ)

.PHONY: all clean fclean re
