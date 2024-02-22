/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:15:19 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/19 14:51:48 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD 256
# endif

int		ft_isalpha(int c);

int		ft_isdigit(int c);

int		ft_isalnum(int c);

int		ft_isascii(int c);

int		ft_isprint(int c);

size_t	ft_strlen(const char *s);

int		ft_toupper(int c);

int		ft_tolower(int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	*ft_memset(void *b, int c, size_t len);

void	ft_bzero(void *s, size_t n);

char	*ft_strchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *str1, const void *str2, size_t n);

void	*ft_memmove(void *dst, const void *src, size_t n);

char	*ft_strdup(const char *s1);

int		ft_atoi(const char *str);

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

char	*ft_itoa(int n);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

void	*ft_calloc(size_t count, size_t size);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char const *pre_s, char const *suf_s);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	**ft_split(char const *s, char c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void*));

void	ft_lstclear(t_list **lst, void (*del)(void*));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_printf(const char *str, ...);

int		printf_putchar(char c);

int		printf_arg_putstr(char *str);

int		printf_void(uintptr_t adress);

int		printf_putnbr(int num);

int		printf_hex(unsigned int num, int hex_case);

int		printf_putstr_backwards(char *str, int i);

int		printf_uint(unsigned int num);

char	*get_next_line(int fd);

char	*gnl_strdup(const char *s, int bytes, int is_leftover);

char	*newline_strdup(char *str);

char	*gnl_strjoin(char const *pref, char const *suff, ssize_t bytes);

char	*malloc_fail_cleanup(char **leftover);

#endif
