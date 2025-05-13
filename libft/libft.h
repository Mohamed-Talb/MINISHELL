/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:32:07 by mtaleb            #+#    #+#             */
/*   Updated: 2025/05/12 11:15:09 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//  csuxXdip
// 012345678
typedef struct flags {
	bool	zero;
	bool	minus;
	bool	plus;
	bool	precision_exist;
	bool	negative;
	bool	space;
	bool	hashtag;
	int		specifier;
	int		precision;
	int		width;
}	t_flag;

// FT_STRINGS:
char	*ft_itoa(int n);
char	**ft_strdup2(char **str);
char	*ft_strdup(const char *s);
char	**ft_lsttostr2(t_list *head);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void ft_remove(char ***str, int index);
char	*ft_append(char *org, char c, int position);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_append2(char **src, char *str, int pos);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strlen2(char **ptr);
int		ft_atoi(const char *nptr);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_freedouble(char ***ptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

//FT_LINKED LIST
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstaddback(t_list **Root, void *content);

void	ft_lstclear(t_list **Head);
void	ft_lstaddfront(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));

int		ft_lstsize(t_list *lst);

// FT_MEMORY MANIPULATION
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

// FT_FD
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

// FT_IS
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_iswhitespace(char c);

// OTHERS
char	*ft_getnextline(int fd);
char	*ft_getenv(char **env, char *varname);

//FT_PRINTF
int		ft_printf(const char *s, ...);
//1- init
void	initflags(t_flag *flag);
int		initstruct(char **str, t_flag *flag);
//2- print 
char	*printmemory(void *addr);
char	*printunsigned(unsigned int n);
char	*printstring(const char *s);
char	*printint(int n, t_flag *params);
int		printchar(int c, int width, bool minus);
char	*printhexa(unsigned int n, char *base, t_flag *params);
//3- check errors
int		checkorder(char *s);
int		checkoverflow(char *s);
char	*checknull(t_flag *params);
// 4- bonus functions
int		width(char *ptr, t_flag *params);
char	*flags(char *ptr, t_flag *params);
char	*precision(t_flag *flag, char *str);
//5- utils 
void	ft_putchar(char c);
void	ft_putstr(char *s);
long	ftnewatoi(char **nptr);
char	*ftappend(char *org, char c, int position);

#endif
