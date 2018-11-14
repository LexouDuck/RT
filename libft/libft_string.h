/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

/*
** ************************************************************************** *|
**                          Basic String Operations                           *|
** ************************************************************************** *|
*/

/*
**	Creates a new string instance of the given 'size',
**	allocating 'n' bytes of memory, and setting every char to '\0'.
*/
char	*ft_strnew(size_t n);

/*
**	Sets every byte of the given string 'str' to 'c', only stopping upon
**	reading a '\0' string terminator character.
*/
void	ft_strset(char *str, char c);

/*
**	Clears the given string 'str', setting each character of 'str' to '\0'.
*/
void	ft_strclr(char *str);

/*
**	Deletes the string pointed to by 'ptr', freeing the associated memory.
*/
void	ft_strdel(char **ptr);

/*
**	Returns a newly allocated string which is a copy of the given string 'str',
**	(or NULL if the required memory could not be allocated).
*/
char	*ft_strdup(char const *str);

/*
**	Copies the given string 'src' into 'dest' (null-terminator included),
**	and returns 'dest' (no allocation is performed).
*/
char	*ft_strcpy(char *dest, char const *src);

/*
**	Copies the first 'n' characters of the given string 'src' into 'dest',
**	and returns 'dest' (no allocation is performed).
*/
char	*ft_strncpy(char *dest, char const *src, size_t n);

/*
**	Copies the given string 'src' into 'dest', null-terminating the result
**	(the '\0' is placed at: ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
size_t	ft_strlcpy(char *dest, char const *src, size_t size);

/*
**	Concatenates the given string 'src' to the end of 'dest',
**	(removing dest's '\0' terminator) and returns 'dest'.
*/
char	*ft_strcat(char *dest, char const *src);

/*
**	Concatenates the first 'n' characters of the given string 'src'
**	to the end of 'dest', and returns 'dest'.
*/
char	*ft_strncat(char *dest, char const *src, size_t n);

/*
**	Concatenates characters of the given string 'src' to the end of 'dest',
**	null-terminating the result (places the '\0' at ('dest' + 'size' - 1)),
**	and returns the resulting size of 'dest'.
*/
size_t	ft_strlcat(char *dest, char const *src, size_t size);

/*
**	Returns a new null-terminated string which is the concatenation
**	of the strings pointed to by 'a_str1' and 'a_str2',
**	freeing the two string buffers 'str1' and 'str2' when finished.
*/
char	*ft_strmerge(char **a_str1, char **a_str2);

/*
**	Returns 'dest', result of the concatenation of 'dest' with 'src'.
**	The previous string buffer 'dest' is freed in the process.
*/
char	*ft_strappend(char **dest, char const *src);

/*
**	Returns 'dest', result of the concatenation of 'src' with 'dest'.
**	The previous string buffer 'dest' is freed in the process.
*/
char	*ft_strprepend(char const *src, char **dest);

/*
** ************************************************************************** *|
**                                String Checks                               *|
** ************************************************************************** *|
*/

/*
**	Returns the length of the given null-terminated string 'str'.
*/
size_t	ft_strlen(char const *str);

/*
**	Compares the two given strings, and returns the first difference
**	between characters encountered (str1[i] - str2[i]).
**	Otherwise, it will return 0 if 'str1' and 'str2' are identical.
*/
int		ft_strcmp(char const *str1, char const *str2);

/*
**	Compares at most 'n' chars of the two given strings, and returns
**	the first difference of characters encountered: (str1[i] - str2[i]).
*/
int		ft_strncmp(char const *str1, char const *str2, size_t n);

/*
**	Returns 1 if the two given strings match, and 0 otherwise.
*/
int		ft_strequ(char const *str1, char const *str2);

/*
**	Returns 1 if the first 'n' chars of the two given strings match,
**	and returns 0 if this is not the case.
*/
int		ft_strnequ(char const *str1, char const *str2, size_t n);

/*
**	Returns 1 if the given string 'str' contains at least one occurence
**	of any character found inside 'charset', returns 0 otherwise.
*/
t_bool	ft_strcontains(char const *str, char const *charset);

/*
**	Returns 1 if all the characters inside the given string 'str'
**	are contained within the string 'charset', returns 0 otherwise.
*/
t_bool	ft_strcontainsonly(char const *str, char const *charset);

/*
**	Returns the amount of occurences of char 'c' in the given string 'str'.
*/
size_t	ft_strcount_char(char const *str, int c);

/*
**	Returns the amount of occurences of 'query' in the given string 'str'.
*/
size_t	ft_strcount_str(char const *str, char const *query);

/*
** ************************************************************************** *|
**                         String Searching/Replacing                         *|
** ************************************************************************** *|
*/

/*
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strchr(char const *str, int c);

/*
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strstr(char const *str, char const *query);

/*
**	Returns a pointer to the last occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strrchr(char const *str, int c);

/*
**	Returns the last occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched).
*/
char	*ft_strrstr(char const *str, char const *query);

/*
**	Returns a pointer to the first occurence of the given character 'c'
**	in the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char	*ft_strnchr(char const *str, int c, size_t n);

/*
**	Returns the first occurence of the string 'query' inside
**	the given string 'str' (or NULL if nothing matched),
**	searching only the first 'n' characters of 'str'.
*/
char	*ft_strnstr(char const *str, char const *query, size_t n);

/*
**	Returns a new null-terminated string which is a copy of 'str', in which
**	all non-printable characters found in 'str' are made into printable
**	ANSI-C '\xHH' escape sequences (where "H"s are lowercase hex digits).
*/
char	*ft_strtoescape(char const *str);

/*
**	Returns a reallocated version of the given string 'dest', in which
**	the string 'str' has been inserted at offset 'index'.
**	The previous string buffer 'dest' is freed in the process.
*/
char	*ft_strinsert(char **dest, char const *src, size_t index);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which all occurences of the string 'query' have been removed.
*/
char	*ft_strremove(char const *str, char const *query);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which 'length' characters starting at 'index' have been removed.
*/
char	*ft_strremovesub(char const *str, size_t index, size_t length);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of an 'old' char is replaced with a 'new' char.
*/
char	*ft_strrep_char(char const *str,
	char old,
	char new);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every char in the 'old' charset is replaced by the
**	corresponding character in the 'new' charset (at the same index).
*/
char	*ft_strrep_charset(char const *str,
	char const *old,
	char const *new);

/*
**	Returns a new null-terminated string which is a copy of 'str',
**	in which every occurence of the string 'old' is replaced with 'new'.
*/
char	*ft_strrep_string(char const *str,
	char const *old,
	char const *new);

/*
** ************************************************************************** *|
**                        Common Whitespace Operations                        *|
** ************************************************************************** *|
*/

/*
**	Returns a new string from 'str' in which all leading and trailing
**	whitespace characters (' ', '\n', '\t') have been removed.
*/
char	*ft_strtrim(char const *str);

/*
**	Returns a new string from 'str' in which all leading
**	characters present in 'charset' have been removed.
*/
char	*ft_strtrim_l(char const *str, char const *charset);

/*
**	Returns a new string from 'str' in which all trailing
**	characters present in 'charset' have been removed.
*/
char	*ft_strtrim_r(char const *str, char const *charset);

/*
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on both sides
**	if the desired 'length' is larger than 'str'.
*/
char	*ft_strpad(char const *str, char c, size_t length);

/*
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	left side if the desired 'length' is larger than 'str'.
*/
char	*ft_strpad_l(char const *str, char c, size_t length);

/*
**	Returns a new null-terminated string duplicate of 'str' which is
**	'length' characters long, by padding it with 'c' chars on its
**	right side if the desired 'length' is larger than 'str'.
*/
char	*ft_strpad_r(char const *str, char c, size_t length);

/*
** ************************************************************************** *|
**                          Other String Operations                           *|
** ************************************************************************** *|
*/

/*
**	Returns a newly allocated string which is a copy of the given string 'str',
**	but in reverse order (except for the \0 terminator, obviously).
*/
char	*ft_strrev(char const *str);

/*
**	Returns a new null-terminated string which is a subsection of 'str',
**	starting at char index 'start' and copying 'length' characters.
*/
char	*ft_strsub(char const *str, size_t start, size_t length);

/*
**	Returns a new null-terminated string which is the result of
**	the concatenation of the two given strings 'str1' and 'str2'.
*/
char	*ft_strjoin(char const *str1, char const *str2);

/*
**	Returns a string array made up of substrings of 'str', where each element
**	is a section delimited by 'c' separators, or the edges of the string.
*/
char	**ft_strsplit(char const *str, char c);

/*
**	Iterates upon each character of the given string 'str',
**	applying the given function 'f' to each of its characters.
*/
void	ft_striter(char *str, void (*f)(char *));

/*
**	Iterates upon each character of the given string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
void	ft_striteri(char *str, void (*f)(unsigned int, char *));

/*
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars.
*/
char	*ft_strmap(char const *str, char (*f)(char));

/*
**	Creates a new null-terminated string by iterating upon the string 'str',
**	applying the function 'f' to each of its chars (with index information).
*/
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));

#endif
