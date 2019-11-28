/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ligft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:53:49 by hturkatr          #+#    #+#             */
/*   Updated: 2019/09/20 14:23:47 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define MAX_LONG  9223372036854775807
# define MIN_LONG  -9223372036854775808
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define MAX_UINT 4294967295
# define MAX_ULONG 18446744073709551615

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_map_item
{
	void				*value;
	void				*key;
	size_t				value_size;
	size_t				key_size;
	struct s_map_item	*next_item;
}					t_map_item;

typedef struct		s_map
{
	t_map_item		*first_item;

	void			(*emplace)(struct s_map *this, t_map_item item);
	t_map_item		*(*find)(struct s_map *this, void *key, size_t key_size);
	void			(*remove)(struct s_map *this, void *key, size_t key_size);
	void			(*erase)(struct s_map *this);
}					t_map;

t_map				*ft_make_t_map(void);
void				ft_destroy_t_map(t_map *object);
void				*ft_memdup(const void *data, size_t data_size);
void				*ft_calloc(size_t size);

/*
**One direction linked list
*/
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
**Compares two strings, returns the result of
**comparison between first unequal pair of chars or zero
*/
int					ft_strcmp(const char *s1, const char *s2);

/*
**Returns the len of a string
*/
size_t				ft_strlen(const char *s);

/*
**Compares first n symbols of two strings
*/
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);

/*
**Mallocs and returns a copy of a string
*/
char				*ft_strdup(const char *s1);

/*
**Copy n symbols of source string to destination string
*/
char				*ft_strncpy(char *dest, const char *src, size_t n);

/*
**Takes array and return it's integer value
*/
int					ft_atoi(const char *str);

/*
**Sets a zero value to memory region
*/
void				ft_bzero(void *s, size_t n);

/*
**Checks string, returns 0 if the string contains only numbers and letters
*/
int					ft_isalnum(int c);

/*
**Checks string, returns 0 if the string contains only letters
*/
int					ft_isalpha(int c);

/*
**Sets a c value to memory region
*/
void				*ft_memset(void *b, int c, size_t len);

/*
**Copy source string to destination string, !unsafe!
*/
char				*ft_strcpy(char *dest, const char *src);

/*
**Checks string, returns 0 if the string contains only digits
*/
int					ft_isdigit(int c);

/*
**Checks whether a string is printable
*/
int					ft_isprint(int c);

/*
**Copy data from source to destination, stops when reach c
*/
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);

/*
**Copy data from source to destination
*/
void				*ft_memcpy(void *dst, const void *src, size_t n);

/*
**Checks whether a string contains only ascii chars
*/
int					ft_isascii(int c);

/*
**Search for a pattern in a string, returns a pointer to it or NULL
*/
char				*ft_strstr(char *str, char *to_find);

/*
**Converts a string to lovercase
*/
int					ft_tolower(int c);

/*
**Converts a string to uppercase
*/
int					ft_toupper(int c);

/*
**Concatenate source string to destination one !unsafe!
*/
char				*ft_strcat(char *dest, const char *src);

/*
**Concatenate n chars from source string to destination one !unsafe!
*/
char				*ft_strncat(char *dest, const char *src, int nb);

/*
**Concatenate source string to destination one
*/
size_t				ft_strlcat(char *dest, const char *src, size_t size);

/*
**Search for a first appearance of char c in a string
*/
char				*ft_strchr(const char *str, int ch);

/*
**Search for a pattern in first n chars of a string,
**returns a pointer to it or NULL
*/
char				*ft_strnstr(const char *str, const char *to_find, size_t n);

/*
**Search for a last appearance of char c in a string
*/
char				*strrchr(const char *string, int symbol);

/*
**Allocates a memory region
*/
void				*ft_memalloc(size_t size);

/*
**Deletes memory region
*/
void				ft_memdel(void **ap);

/*
**Allocate a memory to a new string, sets it's chars to '\0'
*/
char				*ft_strnew(size_t size);

/*
**Deletes string
*/
void				ft_strdel(char **as);

/*
**Sets strings's chars to '\0'
*/
void				ft_strclr(char *s);

/*
**Apply a function f to all chars in a string
*/
void				ft_striter(char *s, void (*f)(char *));

/*
**Apply a function f which takes index
**of a char as an argument to all chars in a string
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*
**Applies the function f to each character of the string
**given as argument to create a “fresh” new string (with malloc(3))
**resulting from the successive applications of f.
*/
char				*ft_strmap(char const *s, char (*f)(char));

/*
**Applies the function f to each character of the string passed as argument
**by giving its index as first argument to create a “fresh” new string
**(with malloc(3)) resulting from the suc- cessive applications of f.
*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
**Lexicographical comparison between s1 and s2.
**If the 2 strings are identical the function returns 1, or 0 otherwise.
*/
int					ft_strequ(char const *s1, char const *s2);

/*
**Lexicographical comparison between s1 and s2 up to n char-
**acters or until a ’\0’ is reached. If the 2 strings are identical,
**the function returns 1, or 0 otherwise.
*/
int					ft_strnequ(char const *s1, char const *s2, size_t n);

/*
**Returns a “fresh” substring from the string given as argument.
**The substring begins at indexstart and is of size len.
*/
char				*ft_strsub(char const *s, unsigned int start, size_t len);

/*
**Returns a “fresh” string end- ing with ’\0’,
**result of the concatenation of s1 and s2
*/
char				*ft_strjoin(char const *s1, char const *s2);

/*
**Prints string, adds newline to it's end
*/
void				ft_putendl(char const *s);

/*
**Prints integer
*/
void				ft_putnbr(int n);

/*
**Prints string
*/
void				ft_putstr(char const *s);

/*
**Prints char
*/
void				ft_putchar(char c);

/*
**Prints string to a file, adds newline to it's end
*/
void				ft_putendl_fd(char const *s, int fd);

/*
**Prints char to a file
*/
void				ft_putchar_fd(char c, int fd);

/*
**Prints string to a file
*/
void				ft_putstr_fd(char const *s, int fd);

/*
**Prints integer to a file
*/
void				ft_putnbr_fd(int n, int fd);

/*
**Create a new linked list element
*/
t_list				*ft_lstnew(void const *content, size_t content_size);

/*
**Trims string
*/
char				*ft_strtrim(char const *s);

/*
**and returns an array of “fresh” strings obtained
**by spliting s using the character c as a delimiter.
*/
char				**ft_strsplit(char const *s, char c);
/*
** Totally useless function!
*/
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

/*
** Use this one instead of ft_lstdelone!
*/
void				ft_lstdel_elem(t_list *elem);

/*
** Totally useless function!
*/
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
** Use this one instead of ft_lstdel!
*/
void				ft_lstdelete(t_list *head);

/*
** Adds new element to a linked list
*/
void				ft_lstadd(t_list **alst, t_list *new);

/*
**Iterates linked list, applies a function to each element
*/
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

/*
**Creates a new list from application of
**function f to each element of original list
*/
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
**Copies linked list's element
*/
t_list				*ft_lst_elem_cpy(t_list *elem);

/*
**Adds element to the end of linked list
*/
void				ft_lst_add_tail(t_list *head, t_list *elem);

/*
**Copies element of a linked list
*/
t_list				*ft_lstcpy(t_list *head);

/*
**Converts an integer to a array of chars
*/
char				*ft_itoa(int n);

/*
**Returns a pointer to a char in memory region
*/
void				*ft_memchr(const void *s, int c, size_t n);

/*
**Compares two memory regions
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
**Moves
*/
void				*ft_memmove(void *dst, void const *src, size_t len);

/*
**Puts a string to an error output
*/
void				ft_puterr(char *err);

/*
**Returns a pointer to last appearance
**of a char c in a string
*/
char				*ft_strrchr(const char *str, int symbol);

/*
**Counts letters in a string
*/
int					ft_countletters(char *str);

/*
**Allocates memory and copies data to it
*/
void				*ft_realloc(void *arr, size_t arr_size, size_t size);

/*
**Cheers you up when you are blue
**Just put a string "I'm sad"
**as an argument
*/
void				ft_cheer_me_up(char *msg);

#endif
