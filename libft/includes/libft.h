/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevy <vlevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:29:00 by vlevy             #+#    #+#             */
/*   Updated: 2023/11/25 17:38:41 by vlevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 555
# endif

# ifndef FD_CAP
#  define FD_CAP 1024
# endif

typedef struct s_clist
{
	char					*content;
	struct s_clist			*next;
}								t_clist;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}								t_list;

typedef struct s_flags
{
	int		f;
	int		sign;
	int		sharp;
	int		pad_side;
	int		pad_sign;
	int		pad_value;
	int		precision;
	int		precision_value;
	int		left_padding_space;
	int		left_padding_zero;
	int		right_padding;
	char	*arg_str;

}							t_flags;
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *s);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_is_space(char c);
int			ft_toupper(int c);
int			ft_tolower(int c);
size_t		ft_strlen(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr_charset(const char *s, const char *charset);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strtrim(const char *s1, const char *set);
char		**ft_split(char const *s, char c);
char		**ft_split_set(char *s, char *charset);
char		*ft_itoa(int n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strdup(const char *s);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **list, t_list *new);
int			ft_lstsize(t_list *list);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char		*get_next_line(int fd);
char		*read_till_eol(char *str, char *stash, t_clist *lst, int fd);
void		ft_strncat(char *dest, char *src, int n);
char		*update_stash(char *stash, t_clist *tmp);
int			update_lst(t_clist **lst, char *buff);
int			find_eol(char *buff);
char		*ft_lst_clear(t_clist **lst);
int			ft_strlen_cs(char *str, char c, int f);

const char	*ft_identifier(va_list *ap, const char *format,
				long *count);
const char	*ft_pad_check(const char *format, t_flags *flags);
const char	*flag_check(const char *format, t_flags *flags);
int			ft_printf(const char *format, ...);
void		init_flags(t_flags *flags);
int			def_padding(t_flags *flags);
char		*fill_padding(char *pad_str, t_flags *flags);
char		*ft_itoa_base(long nb, char *base);
char		*ft_itoa_ptr(unsigned long long nb, char *base);
int			ft_printf(const char *format, ...);
int			malloc_secure(char *str, long *count);
char		*char_padding(char *pad_str, t_flags *flags, long *count);

void		ft_char_handling(va_list *ap, long *count, t_flags *flags);
void		ft_str_handling(va_list *ap, long *count, t_flags *flags);
void		ft_int_handling(va_list *ap, long *count, t_flags *flags);
void		ft_unsgnd_int_handling(va_list *ap, long *count,
				t_flags *flags);
void		ft_lchexa_handling(va_list *ap, long *count,
				t_flags *flags);
void		ft_uchhexa_handling(va_list *ap, long *count,
				t_flags *flags);
void		ft_ptr_handling(va_list *ap, long *count, t_flags *flags);
void		ft_free_tab(char **tab);
void		ft_free_n_tab(char **tab, size_t tab_size);
double		ft_atod(char *str);

#endif
