/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaleb <mtaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:32:07 by mtaleb            #+#    #+#             */
/*   Updated: 2025/07/19 10:39:13 by mtaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>
# include "ft_cleaner/cleaner.h"

#define L_OVERFLOW 9223372036854775808ULL

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
	int		write_dest;
}	t_flag;

// FT_STRINGS:
char	*ft_itoa(int n);
int		atoi_sign(char *nptr);
char	**ft_strdup2(char **str);
char	*ft_uitoa(unsigned int n);
char	*ft_strdup(const char *s);
void 	ft_printdoule(char **str);
char	*ft_strchr(const char *s, int c);
unsigned long long	ft_atoi_l(char *nptr);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char 	*ft_remove(char *str, int pos);
char 	**ft_remove2(char **str, int index);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);

// APPEND
char	*append(char *org, char c);
char	*fappend(char *org, char c);
char	*pappend(char *org, char c, int position);
char	*ft_append(char *org, char c, int position);
char	**ft_append2(char **src, char *str, int pos);

int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strlen2(char **ptr);
int		ft_atoi(const char *nptr);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	ft_freedouble(char **ptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);


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
void *ft_malloc(size_t size);

//PRINTERS
int		eputf(const char *s, ...);
int		ft_printf(const char *s, ...);
int		veputf(const char *s, va_list args);
//1- init
void	initflags(t_flag *flag);
int		initstruct(char **str, t_flag *flag);
//2- print 
char	*printmemory(void *addr);
char	*printunsigned(unsigned int n);
char	*printstring(const char *s);
char	*printint(int n, t_flag *params);
int		printchar(int c, int width, bool minus, int write_dest);
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
