/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:33:37 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/19 22:36:30 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H

# include "libft.h"
# include "libft_mem.h"

/*
** =========== Character Functions ==========
*/

/*
** Returns 1 if the given char 'c' is a letter (lowercase or uppercase), and
** 0 otherwise.
*/
int						ft_isalpha(int c);

/*
** Returns 1 if the given char 'c' is uppercase, and 0 otherwise.
*/
int						ft_isupper(int c);
/*
** Returns 1 if the given char 'c' is lowercase, and 0 otherwise.
*/
int						ft_islower(int c);

/*
** Returns 1 if the given char 'c' is a numerical digit, and 0 otherwise.
*/
int						ft_isdigit(int c);

/*
** Returns 1 if the given char 'c' is alphanumeric (number or letter), and 0
** otherwise.
*/
int						ft_isalnum(int c);

/*
** Returns 1 if the given char 'c' has a value between 0 and 127, and 0
** otherwise.
*/
int						ft_isascii(int c);

/*
** Returns 1 if the given char 'c' is \t, \n, \v, \r or \f, and 0 otherwise.
*/
int						ft_isspace(int c);

/*
** Returns 1 if the given char 'c' is a printable ASCII character, and 0
** otherwise.
*/
int						ft_isprint(int c);

/*
** Returns the uppercase equivalent of the given char 'c' (nothing is done
** if 'c' is not a letter).
*/
int						ft_toupper(int c);

/*
** Returns the lowercase equivalent of the given char 'c' (nothing is done
** if 'c' is not a letter).
*/
int						ft_tolower(int c);

/*
** ============ String Const or Utils Functions ===========
*/

/*
** Returns the length of the given null-terminated string 'str'.
*/

size_t					ft_strlen(char const *str);

/*
** Creates a new string of the given 'size', allocating memory, setting
** each element to '\0'.
*/
char					*ft_strnew(size_t size);

/*
** Returns a newly-allocated string of size 'size' set to 'c'.
*/
char					*ft_strcnew(size_t size, char const c);

/*
** Deletes the string pointed to by 'ptr', freeing memory.
*/
void					ft_strdel(char **ptr);

/*
** Clears the given string 's', setting each element to '\0'.
*/
void					ft_strclr(char *str);

/*
** Returns a newly allocated string which is a copy of the given string
** 'str' (or NULL if the required memory could not be allocated).
*/
char					*ft_strdup(char const *str);

/*
** Returns a newly-allocated copy of str, considering c as an additional
** terminating character for str.
*/
char					*ft_strcdup(char const *str, char const c);

/*
** Returns a big-endian hexadecimal string of the elements of str considered
** as unsigned char.
*/
char					*ft_strhex(char const *str);

/*
** Returns a newly allocated string containing the same characters as
** 'str', in reverse order.
*/
char					*ft_strrev(char const *str);

/*
** Copies the given string 'src' into 'dest' (null-terminator included),
** and returns 'dest'.
*/
char					*ft_strcpy(char *dest, char const *src);

/*
** Copies the first 'n' characters of the given string 'src' into 'dest',
** and returns 'dest'.
*/
char					*ft_strncpy(char *dest, char const *src, size_t n);

/*
** Copies the given string 'src' into 'dest', null-terminating 'dest'
** (the '\0' is placed at ('size' - 1)), and it returns the resulting
** size of 'dest'.
*/

size_t					ft_strlcpy(char *dest, char const *src, size_t size);

/*
** Concatenates the given string 'src' to the end of 'dest', and returns 'dest'.
*/
char					*ft_strcat(char *dest, char const *src);

/*
** Concatenates the first 'n' characters of the given string 'src' to the end
** of 'dest', and returns 'dest'.
*/
char					*ft_strncat(char *dest, char const *src, size_t n);

/*
** Concatenates up to ('size' - 1) characters of the given string 'src' to the
** end of 'dest', null-terminating the result, and returning the resulting size.
*/
size_t					ft_strlcat(char *dest, char const *src, size_t size);

/*
** Returns a newly allocated string, the result of the concatenation of s1
** containing the character c a total of n times, and a string s2 == s.
*/
char					*ft_strpad_left(char const *s, char const c, t_u32 n);

/*
** Returns a newly allocated string, the result of the concatenation of a string
** s1 == s and s2 containing the character c a total of n times.
*/
char					*ft_strpad_right(const char *s, const char c, t_u32 n);

/*
** Returns a pointer to the first occurence of a char 'c' in the given string
** 'str' (or NULL if nothing matched).
*/
char					*ft_strchr(char const *str, int c);

/*
** Returns a pointer to the last occurence of a char 'c' in the given string
** 'str' (or NULL if nothing matched).
*/
char					*ft_strrchr(char const *str, int c);

/*
** Returns the first index at which c is found in str, or -1 if c is absent.
*/
int						ft_strfind(char const *str, int c);

/*
** Returns the first occurence of the string 'sub' inside the given string
** 'str' (or NULL if nothing matched).
*/
char					*ft_strstr(char const *str, char const *sub);

/*
** Returns the first occurence of the string 'sub' inside the given string
** 'str' (or NULL if nothing matched), searching only the first 'n' bytes.
*/
char					*ft_strnstr(char const *str, char const *sub, size_t n);

/*
** Returns the index of the first occurrence of sub in str, or -1 upon failure.
*/
int						ft_stristr(char const *str, char const *sub);

/*
** Compares the two given strings, and returns the first difference of
** characters encountered: (str1[i] - str2[i]). NULL input treated like
** empty string.
*/
int						ft_strcmp(char const *s1, char const *s2);

/*
** Compares at most 'n' chars of the two given strings, and returns the
** first difference of characters encountered: (str1[i] - str2[i]).
*/
int						ft_strncmp(char const *s1, char const *s2, size_t n);

/*
** Returns 1 if the two given strings match, and 0 otherwise.
*/
int						ft_strequ(char const *s1, char const *s2);

/*
** Returns 1 if the first 'n' chars of the two given strings match, and 0
** otherwise.
*/
int						ft_strnequ(char const *s1, char const *s2, size_t n);

/*
** Iterates upon the given string 'str', applying the function 'f' to each
** of its elements.
*/
void					ft_striter(char *str, void (*f)(char *));

/*
** Iterates upon the given string 'str', applying the function 'f' to each
** of its elements (with index information).
*/
void					ft_striteri(char *str, void (*f)(unsigned int, char *));

/*
** Creates a new string by iterating upon the string 'str', applying the
** function 'f' to each of its chars.
*/
char					*ft_strmap(char const *str, char (*f)(char));

/*
** Creates a new string by iterating upon the string 'str', applying the
** function 'f' to each of its chars (with index information).
*/
char					*ft_strmapi(char const *str, char (*f)(t_u32, char));

/*
** Returns a new string which is a subsection of 'str', starting at 'start'
** and copying 'len' characters. Only returns NULL upon malloc failure, else
** returns an newly-allocated empty string.
*/
char					*ft_strsub(char const *str, t_u32 start, size_t len);

/*
** Returns a new string which is the result of the concatenation of the
** two given strings.
*/
char					*ft_strjoin(char const *str1, char const *str2);

/*
** Returns a new string from 'str' in which all leading and trailing
** whitespace characters (' ', '\n', '\t') have been removed.
*/
char					*ft_strtrim(char const *str);

/*
** Converts non-printable characters into ASCII printable '\xhh', where h is a
** HXLOW digit.
*/
char					*ft_str_toprint(char const *str);

/*
** Returns a newly allocated version of str where all instances of "sub"
** have been removed.
*/
char					*ft_strremove(char const *str, char const *sub);

/*
** Returns a newly allocated version of str where all instances of "sub"
** have been replaced by "rep".
*/
char					*ft_strreplace(char const *str, char const *sub,
										char const *rep);

/*
** Returns the number of occurences of c in str.
*/
t_u32					ft_str_countchar(char const *str, char const c);

/*
** Returns True iff the chars that compose 'str' are all in the set 'chars'
*/
int						ft_str_containsonly(char const *str, char const *chars);

/*
**  ============ String by Address Functions ===========
*/

/*
** Returns a new concatenation of s1 and s2, and frees them as needed.
*/
char					*ft_strmerge(char **a_s1, char **a_s2);

/*
** Returns the concatenation of dest and src inside the pointer of dest.
** The previous dest is freed and src is unaltered.
*/
char					*ft_strappend(char **dest, char const *src);

/*
** Returns the concatenation of src and dest inside the pointer of dest.
** The previous dest is free and src is unaltered.
*/
char					*ft_strprepend(char const *src, char **dest);

/*
** Reallocs dest, and inserts src at index, and appends the substring of dest
** that was after index.
*/
char					*ft_strinsert(char **dest, char const *src,
										t_u32 index);

/*
** Edits "str" so that all instances of "sub" are replaced by "rep".
*/
void					ft_strreplace_inplace(char **a_str, char const *sub,
										char const *rep);

/*
** Flips a string's order on itself. Reallocates.
*/
void					ft_strrev_inplace(char **a_str);

/*
** Works like the bash function tr. Substitute tr_f[i] by tr_t[i] in str.
** Fails silently if input is null, if strlen is different for tr_f and tr_t,
** or if a character is repeated in tr_f (only one image for every antecedent).
*/
void					ft_str_csubstitute(char *str, char const *tr_f,
											char const *tr_t);

/*
** Returns the same string with all characters in uppercase.
** TODO make it an inline call to str_csubstitute ?
*/
void					ft_str_toupper(char *str);

/*
** Returns ft_strpad_left by reference rather than new allocation.
*/
void					ft_strpad_left_inplace(char **a_str,
											char const c, t_u32 len);

/*
** Returns ft_strpad_right by reference rather than new allocation.
*/
void					ft_strpad_right_inplace(char **a_str,
											char const c, t_u32 len);

/*
** Returns an insertion of a string containing 'len' times the character 'c'
** at index 'start' of reference 'a_str'.
*/
void					ft_strpad_insert_inplace(char **a_str, char const c,
										t_u32 start, size_t len);

/*
** Returns str but where the substring defined by start and len have been
** removed.
*/
void					ft_strsub_rm_inplace(char **a_str,
										t_u32 start, size_t len);

/*
** Returns Reallocates 'str' so that all leading characters equal to
** 'c' have been removed.
*/
void					ft_strctrim_left_inplace(char **a_str, char const c);

/*
** Returns Reallocates 'str' so that all trailing characters equal to
** 'c' have been removed.
*/
void					ft_strctrim_right_inplace(char **a_str, char const c);

/*
** Returns Reallocates 'str' so that n leading characters are removed.
*/
void					ft_strntrim_left_inplace(char **a_str, size_t n);

/*
** Returns Reallocates 'str' so that n trailing characters are removed.
*/
void					ft_strntrim_right_inplace(char **a_str, size_t n);

/*
** ============ StrLs Functions ===========
**
** NB : ptrarrnew and ptrarrlen, often used with strls, are in libft_mem.h
*/

/*
** Returns a 2D rectangle of dimensions (y,x), 2D-null-terminated and set to 0.
*/
char					**ft_strlsnew(t_u32 y, size_t x);

/*
** Creates a 2D rectangle of newly allocated memory, all set to c,
** all null-terminated.
*/
char					**ft_strlscnew(t_u32 y, size_t x, char const c);

/*
** Frees a regular nul-term array of nul-term strings and NULLs appropriate
** pointers.
*/
void					ft_strlsdel(char ***a_strls);

/*
** Returns a newly allocated string that is the sum of strings in strls, and
** the string sep has been added between each string. All arguments must be
** properly null-terminated.
*/
char					*ft_strlsjoin(char const **strls, char const *sep);

/*
** Returns a newly allocated strls from a str, which is divided into regular
** intervals of length n. str must be null-terminated.
*/
char					**ft_strdivide(char const *str, size_t n);

/*
** Returns an array of substrings of 'str', where each element is a section
** delimited by 'c' separators, or the edges of the string.
*/
char					**ft_strcsplit(char const *str, char c);

/*
** Returns an array of substrings of 'str', where any c in sep_chars is
** considered whitespace that delimits strings.
*/
char					**ft_split(char const *str, char const *sep_chars);

/*
** Returns an array of substrings of 'str', where 'sub' acts as a separator.
** If "" is used as sub, will return a division into letters.
*/
char					**ft_strsplitstr(char const *str, char const *sub);

/*
** Returns a newly allocated sub-stringlist from strls, similarly to ft_strsub.
*/
char					**ft_strlssub(char const **strls,
										t_u32 start, t_u32 len);

/*
** Returns a newly-allocated strls which is the result of applying the protocol
** 'f' to every string of 'strls'.
*/
char					**ft_strlsmap(char const **strls,
										char*(*f)(char const*));

/*
** Returns strls where every string has been replaced and/or reallocated
** properly according to the protocol given by f. Should also work with
** functions that edit a string in place and return its address.
*/
void					ft_strlsmap_inplace(char ***a_strls,
											char*(*f)(char*));

/*
** Returns the number of occurences of 'c' in strls.
*/
t_u32					ft_strls_countchar(char const **strls, char const c);

/*
** Returns a newly allocated string list, where each line is the result of
** the appropriate ft_strpad_left of length n.
*/
char					**ft_strlspad_left(char const **strls,
											char const c, t_u32 n);

#endif
