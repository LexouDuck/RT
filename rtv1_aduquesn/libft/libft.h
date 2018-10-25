/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:32:36 by aduquesn          #+#    #+#             */
/*   Updated: 2018/07/08 18:35:45 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# include "get_next_line.h"

# define OK		0
# define ERROR	1

# define STDIN	0
# define STDOUT	1
# define STDERR	2

typedef unsigned char	t_u8;
typedef unsigned short	t_u16;
typedef unsigned int	t_u32;
typedef	unsigned long	t_u64;
typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;

typedef struct			s_uple
{
	void				*elements;
	size_t				elem_size;
	size_t				length;
}						t_uple;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

/*
** ============ Memory Functions ===========
*/

/*
** Allocates 'size' bytes in memory, returning the pointer at which
** said bytes were allocated, or NULL if the memory could not be allocated.
*/
void					*ft_memalloc(
		size_t size);

/*
** Frees the allocated memory at '**ptr', and sets '*ptr' as NULL.
*/
void					ft_memdel(
		void **ptr);

/*
** Fills 'n' bytes of memory with 0s, starting at 'ptr'.
*/
void					ft_bzero(
		void *ptr,
		size_t n);

/*
** Fills 'n' bytes of memory with 'byte' (taking only
** the first 8 bits of this int arg), starting at 'ptr'.
*/
void					*ft_memset(
		void *ptr,
		int byte,
		size_t n);

/*
** Copies 'n' bytes of memory from 'src' to 'dest', and returns 'dest'.
*/
void					*ft_memcpy(
		void *dest,
		void const *src,
		size_t n);

/*
** Copies at most 'n' bytes of memory from 'src' to 'dest',
** stopping after the first occurence of a byte equal to 'byte',
** and returns a pointer to ('byte' + 1) in 'dest', or NULL.
*/
void					*ft_memccpy(
		void *dest,
		void const *src,
		int byte,
		size_t n);

/*
** Reads 'n' bytes of memory from 'src' then writes those bytes to 'dest'.
** This function is useful if 'src' and 'dest' overlap.
*/
void					*ft_memmove(
		void *dest,
		void const *src,
		size_t n);

/*
** Returns a newly allocated region of 'n' bytes of memory,
** which are copied from ('src' + 'offset').
*/
void					*ft_memsub(
		void const *ptr,
		size_t offset,
		size_t n);

/*
** Returns a pointer to the first occurrence of a byte equal to 'byte'
** (or NULL if no byte was a match), starting the search at 'ptr'
** and searching 'n' bytes of memory.
*/
void					*ft_memchr(
		void const *ptr,
		int byte,
		size_t n);

/*
** Compares 'n' bytes of memory at 'ptr1' and 'ptr2',
** returning (byte1 - byte2) at the first difference encountered.
*/
int						ft_memcmp(
		void const *ptr1,
		void const *ptr2,
		size_t n);

/*
** Swaps the two numbers pointed to by 'ptr1' and 'ptr2'
** (they must both be of the same 'size').
*/
void					ft_swap(
		void *ptr1,
		void *ptr2,
		size_t size);

/*
** Returns a subsection of the value at 'ptr',
** taking 'length' bits at the given bit index 'bit'
** and bitshifting that value to the right by 'bit' bits.
*/
t_u64					ft_getbits(
		void *ptr,
		int bit,
		int length);

/*
** ========== Conversion Functions ==========
*/

/*
** Returns an int parsed from the given string number 'str'
** (returns 0 if 'str' is invalid).
*/
int						ft_atoi(char const *str);
/*
** Returns an int parsed from the given string hexadecimal number 'str'
** (returns 0 if 'str' is invalid- it's ok if there is a "0x" prefix).
*/
int						ft_atoi_hex(char const *str);
/*
** Returns an integer parsed from the given string number 'str',
** according to the given 'base' characterset string.
** (returns 0 if either 'str' or 'base' are invalid).
*/
int						ft_atoi_base(char const *str, char const *base);

/*
** Returns a newly allocated string which is the
** string representation of the given int 'number'.
*/
char					*ft_itoa(int number);
/*
** Returns a newly allocated string which is the
** hexadecimal string representation of the given 'number'
** (starting with the given 'prefix', typically "0x").
*/
char					*ft_itoa_hex(unsigned int number, char const *prefix);
/*
** Returns a newly allocated string which is the
** string representation of 'number', according to the given number 'base'
** (returns NULL if 'base' is invalid).
*/
char					*ft_itoa_base(int number, char const *base);

/*
** Returns an floating-point numbee parsed from the given string number 'str'
** (returns 0.0 if 'str' is invalid).
*/
float					ft_atof(char const *str);
/*
** Returns a newly allocated string which is the string representation of
** the given float 'number', with 'precision' digits after the decimal point.
*/
char					*ft_ftoa(float number, int precision);

/*
** =========== Character Functions ==========
*/

/*
** Returns 1 if the given char 'c' is a letter (lowercase or uppercase),
** and returns 0 otherwise.
*/
int						ft_isalpha(int c);
/*
** Returns 1 if the given char 'c' is a numerical digit,
** and returns 0 otherwise.
*/
int						ft_isdigit(int c);
/*
** Returns 1 if the given char 'c' is alphanumeric (number or letter),
** and returns 0 otherwise.
*/
int						ft_isalnum(int c);
/*
** Returns 1 if the given char 'c' has a value between 0 and 127,
** and returns 0 otherwise.
*/
int						ft_isascii(int c);
/*
** Returns 1 if the given char 'c' is a printable ASCII character,
** and returns 0 otherwise.
*/
int						ft_isprint(int c);
/*
** Returns 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
** (carriage return, newline, form feed, vertical tab, tab, or space),
** and returns 0 otherwise.
*/
int						ft_isspace(int c);

/*
** Returns the uppercase equivalent of the given character 'c'
** (nothing is done if 'c' is not a letter character).
*/
int						ft_toupper(int c);
/*
** Returns the lowercase equivalent of the given character 'c'
** (nothing is done if 'c' is not a letter character).
*/
int						ft_tolower(int c);

/*
** ============ String Functions ===========
*/

/*
** Returns the length of the given null-terminated string 'str'.
*/
size_t					ft_strlen(
		char const *str);
/*
** Creates a new string of the given 'size',
** allocating 'size' bytes of memory, setting every char to '\0'.
*/
char					*ft_strnew(
		size_t size);
/*
** Deletes the string pointed to by 'ptr', freeing the associated memory.
*/
void					ft_strdel(
		char **ptr);
/*
** Clears the given string 'str', setting each character of 'str' to '\0'.
*/
void					ft_strclr(
		char *str);
/*
** Returns a newly allocated string which is a copy of the given string 'str',
** (or NULL if the required memory could not be allocated).
*/
char					*ft_strdup(
		char const *str);
/*
** Returns a newly allocated string which is a copy of the given string 'str',
** but in reverse order (except for the \0 terminator, obviously).
*/
char					*ft_strrev(
		char const *str);

/*
** Copies the given string 'src' into 'dest' (null-terminator included),
** and returns 'dest' (no allocation is performed).
*/
char					*ft_strcpy(
		char *dest,
		char const *src);
/*
** Copies the first 'n' characters of the given string 'src' into 'dest',
** and returns 'dest' (no allocation is performed).
*/
char					*ft_strncpy(
		char *dest,
		char const *src,
		size_t n);
/*
** Copies the given string 'src' into 'dest', null-terminating the result
** (the '\0' is placed at: ('dest' + 'size' - 1)),
** and returns the resulting size of 'dest'.
*/
size_t					ft_strlcpy(
		char *dest,
		char const *src,
		size_t size);

/*
** Concatenates the given string 'src' to the end of 'dest',
** (removing 'dest's \0 terminator) and returns 'dest'.
*/
char					*ft_strcat(
		char *dest,
		char const *src);
/*
** Concatenates the first 'n' characters of the given string 'src'
** to the end of 'dest', and returns 'dest'.
*/
char					*ft_strncat(
		char *dest,
		char const *src,
		size_t n);
/*
** Concatenates characters of the given string 'src' to the end of 'dest',
** null-terminating the result (places the '\0' at ('dest' + 'size' - 1)),
** and returns the resulting total size of 'dest'.
*/
size_t					ft_strlcat(
		char *dest,
		char const *src,
		size_t size);

/*
** Returns a pointer to the first occurence of the given character 'c'
** in the given string 'str' (or NULL if nothing matched).
*/
char					*ft_strchr(
		char const *str,
		int c);
/*
** Returns a pointer to the last occurence of the given character 'c'
** in the given string 'str' (or NULL if nothing matched).
*/
char					*ft_strrchr(
		char const *str,
		int c);

/*
** Returns the first occurence of the string 'query' inside
** the given string 'str' (or NULL if nothing matched).
*/
char					*ft_strstr(
		char const *str,
		char const *query);
/*
** Returns the first occurence of the string 'query' inside
** the given string 'str' (or NULL if nothing matched),
** searching only the first 'n' characters of 'str'.
*/
char					*ft_strnstr(
		char const *str,
		char const *query,
		size_t n);

/*
** Compares the two given strings, and returns the first difference
** between characters encountered (str1[i] - str2[i]), or 0 if they're equal.
*/
int						ft_strcmp(
		char const *str1,
		char const *str2);
/*
** Compares at most 'n' chars of the two given strings, and returns
** the first difference of characters encountered: (str1[i] - str2[i]).
*/
int						ft_strncmp(
		char const *str1,
		char const *str2,
		size_t n);

/*
** Returns 1 if the two given strings match, and 0 otherwise.
*/
int						ft_strequ(
		char const *str1,
		char const *str2);
/*
** Returns 1 if the first 'n' chars of the two given strings match,
** and returns 0 if this is not the case.
*/
int						ft_strnequ(
		char const *str1,
		char const *str2,
		size_t n);

/*
** Iterates upon each character of the given string 'str',
** applying the given function 'f' to each of its characters.
*/
void					ft_striter(
		char *str,
		void (*f)(char *));
/*
** Iterates upon each character of the given string 'str',
** applying the function 'f' to each of its chars (with index information).
*/
void					ft_striteri(
		char *str,
		void (*f)(unsigned int, char *));

/*
** Creates a new null-terminated string by iterating upon the string 'str',
** applying the function 'f' to each of its chars.
*/
char					*ft_strmap(
		char const *str,
		char (*f)(char));
/*
** Creates a new null-terminated string by iterating upon the string 'str',
** applying the function 'f' to each of its chars (with index information).
*/
char					*ft_strmapi(
		char const *str,
		char (*f)(unsigned int, char));

/*
** Returns a new null-terminated string which is a subsection of 'str',
** starting at char index 'start' and copying 'length' characters.
*/
char					*ft_strsub(
		char const *str,
		size_t start,
		size_t length);

/*
** Returns a new null-terminated string which is a copy of 'str'
** that is 'length' chars long, padding it on both sides with
** 'c' chars if needed (the given 'str' is center-justified).
*/
char					*ft_strpad(
		char const *str,
		char c,
		size_t length);
/*
** Returns a new null-terminated string which is a copy of 'str'
** that is 'length' chars long, padding it with 'c' chars on its
** left side if needed.
*/
char					*ft_strpad_l(
		char const *str,
		char c,
		size_t length);
/*
** Returns a new null-terminated string which is a copy of 'str'
** that is 'length' chars long, padding it with 'c' chars on its
** right side if needed.
*/
char					*ft_strpad_r(
		char const *str,
		char c,
		size_t length);

/*
** Returns a new string from 'str' in which all leading and trailing
** whitespace characters (' ', '\n', '\t') have been removed.
*/
char					*ft_strtrim(
		char const *str);
/*
** Returns a new string from 'str' in which all leading
** characters present in 'charset' have been removed.
*/
char					*ft_strtrim_l(
		char const *str,
		char const *charset);
/*
** Returns a new string from 'str' in which all trailing
** characters present in 'charset' have been removed.
*/
char					*ft_strtrim_r(
		char const *str,
		char const *charset);

/*
** Returns a new null-terminated string which is the result of
** the concatenation of the two given strings 'str1' and 'str2'.
*/
char					*ft_strjoin(
		char const *str1,
		char const *str2);

/*
** Returns an array of substrings of 'str', where each element is
** a section delimited by 'c' separators, or the edges of the string.
*/
char					**ft_strsplit(
		char const *str,
		char c);

/*
** Returns a new null-terminated string which is a copy of 'str',
** in which every 'c_old' char is replaced with 'c_new'.
*/
char					*ft_strrep_char(
		char const *str,
		char c_old, char c_new);
/*
** Returns a new null-terminated string which is a copy of 'str',
** in which every char in 'charset' is replaced by 'c'.
*/
char					*ft_strrep_charset(
		char const *str,
		char const *charset,
		char c);
/*
** Returns a new null-terminated string which is a copy of 'str',
** in which every instance of 'old' is replaced with 'new'.
*/
char					*ft_strrep_string(
		char const *str,
		char *old,
		char *new);

/*
** ============ Write Functions ============
*/

/*
** Writes the given char 'c' to the standard output.
*/
void					ft_putchar(char c);
/*
** Writes the given string 'str' to the standard output.
*/
void					ft_putstr(char const *str);
/*
** Writes the given string 'str' to the standard output,
** with a newline at the end of it.
*/
void					ft_putendl(char const *str);
/*
** Writes a string of the given 'number' to the standard output.
*/
void					ft_putnbr(int number);

/*
** Writes the given char 'c' to the given file descriptor 'fd'.
*/
void					ft_putchar_fd(char c, int fd);
/*
** Writes the given string 'str' to the given file descriptor 'fd'.
*/
void					ft_putstr_fd(char const *str, int fd);
/*
** Writes the given string 'str' to the given file descriptor 'fd',
** with a newline at the end of it.
*/
void					ft_putendl_fd(char const *str, int fd);
/*
** Writes a string of the given 'number' to the given file descriptor 'fd'.
*/
void					ft_putnbr_fd(int number, int fd);

/*
** ============= List Functions =============
*/

/*
** Allocates and returns a new element of a list,
** according to the given arguments.
*/
t_list					*ft_lstnew(
		void const *content,
		size_t content_size);
/*
** Inserts a new element of a list 'elem' at the pointer '*alst',
** chaining this new element with the next element of this list.
*/
void					ft_lstadd(
		t_list **alst,
		t_list *elem);
/*
** Appends the element 'new_elem' to the end of the list starting at '*alst'.
** If 'alst' is NULL, it will create
*/
void					ft_lstappend(
		t_list **alst,
		t_list *elem);
/*
** Deletes the given element pointed to by 'alst' with the function 'del',
** and then frees memory and sets '*alst' as a NULL pointer.
*/
void					ft_lstdelone(
		t_list **alst,
		void (*del)(void *, size_t));
/*
** Deletes all the elements in the list starting at '*alst',
** calls 'del' and frees memory for each, and lastly sets '*alst' as NULL.
*/
void					ft_lstdel(
		t_list **alst,
		void (*del)(void *, size_t));
/*
** Returns the amount of elements in the given list 'lst'.
*/
int						ft_lstsize(
		t_list *lst);
/*
** Returns the 'index'th element in the given list 'alst'.
** Will return NULL if 'index' is beyond the last element.
*/
t_list					*ft_lstget(
		t_list **alst,
		t_u32 index);
/*
** Returns a subsection of the given list 'alst',
** starting at 'index' and copying 'length' elements.
** Will return NULL if 'index' is too large or length is 0.
** If 'index' is valid but the list is not large enough for 'length',
** then the resulting list will have fewer than 'length' elements.
*/
t_list					**ft_lstsub(
		t_list **alst,
		t_u32 index,
		t_u32 length);
/*
** Iterates upon each element of the given list 'lst',
** applying the given function 'f' to each of its elements.
*/
void					ft_lstiter(
		t_list *lst,
		void (*f)(t_list *));
/*
** Creates a new list which is the result of applying
** the given function 'f' to each element of 'lst'.
*/
t_list					*ft_lstmap(
		t_list *lst,
		t_list *(*f)(t_list *));

/*
** Creates a new contiguous array from the given linked list.
** Returns NULL if elements of 'alst' are of unequal size.
** The array will be terminated with the value pointed to by
** the given 'terminator' pointer (or not, if pointer is NULL).
*/
void					*ft_array_fixed(
		t_list **alst,
		void *terminator);
/*
** Creates a new jagged array (2d) from the given linked list.
** The top-level pointer array is null-terminated.
*/
void					**ft_array(
		t_list **alst);

#endif
