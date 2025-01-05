/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:49:26 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 18:15:15 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define PRIME_MULTIPLIER 37
# define MAX_HASHMAP_SIZE 1024

// Part 1 - Libc functions. Mandatory
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
long			ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *src, size_t n);
void			ft_write(char *s, int fd);
void			ft_str_builder(char *res, size_t res_size, ...);

// Part 2 - Additional functions
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
// also used in ft_split_mult
int				do_copy(char **dst, int length, const char *s, int start);
char			**ft_split_mult(char *str, char *charset);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

// Bonus part
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new_lst);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new_lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

// gnl utils
char			*ft_read(int fd, char *remainder);
char			*ft_free(char *remainder, char *buffer);

// gnl
char			*get_next_line(int fd);

// hashmap
typedef struct s_hashmap_entry
{
	char					*key;
	char					*value;
	struct s_hashmap_entry	*next;
}	t_hashmap_entry;

// todo: once dynamic resize is implemented remove count and use size
typedef struct s_hashmap
{
	t_hashmap_entry	**entries;
	size_t			size;
	size_t			count;
}	t_hashmap;

t_hashmap		*ft_hashmap_create(size_t size);
void			ft_hashmap_free(t_hashmap *map);
int				ft_hashmap_insert(t_hashmap *map,
					const char *key, const char *value);
t_hashmap_entry	*ft_hashmap_get_entry(t_hashmap *map, const char *key);
char			*ft_hashmap_get_value(t_hashmap *map, const char *key);
void			ft_hashmap_free(t_hashmap *map);
void			ft_hashmap_remove(t_hashmap *map, char *key);

// hashmap utils
unsigned int	ft_hash(const char *key, size_t size);
void			ft_hashmap_free(t_hashmap *map);

// hashmap iteri
void			ft_hashmap_iteri(t_hashmap *map,
					void (*f)(t_hashmap_entry *entry));

typedef struct s_pair
{
	void	*first;
	void	*second;
}	t_pair;

// t_pair
t_pair			*create_pair(char *first, char *second);
void			free_pair(t_pair *pair);


// array list
typedef struct s_array_list
{
	char	**data;
	int		size;
	int		capacity;
}	t_array_list;

int				find_matched_key(char *key, char **envp);
t_array_list	*array_list_create(size_t initial_capacity);
void			array_list_add(t_array_list *list, char *element);
void			array_list_remove(t_array_list *list, char *element);
char			*array_list_remove_with_index(t_array_list *list, int index);
void			array_list_free(t_array_list *list);
char			**get_data(t_array_list *list);

#endif
