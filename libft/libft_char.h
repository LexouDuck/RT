/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_char.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CHAR_H
# define LIBFT_CHAR_H

# include "libft.h"

/* ************************************************************************** */
/*                                  Macros                                    */
/* ************************************************************************** */



/* ************************************************************************** */
/*                              Character Checks                              */
/* ************************************************************************** */

/*	@	ctype.h > isalpha()
**	Returns 1 if the given char 'c' is a letter (lowercase or uppercase),
**	and returns 0 otherwise.
*/
int		FT_IsLetter(int c);

/*	@	ctype.h > isupper()
**	Returns 1 if the given char 'c' is a uppercase letter character,
**	and returns 0 otherwise.
*/
int		FT_IsUppercase(int c);

/*	@	ctype.h > islower()
**	Returns 1 if the given char 'c' is an lowercase letter character,
**	and returns 0 otherwise.
*/
int		FT_IsLowercase(int c);

/*	@	ctype.h > isalnum()
**	Returns 1 if the given char 'c' is alphanumeric (number or letter),
**	and returns 0 otherwise.
*/
int		FT_IsAlphanumeric(int c);

/*	@	ctype.h > isspace()
**	Returns 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
**	(carriage return, newline, form feed, vertical tab, tab, or space),
**	and returns 0 otherwise.
*/
int		FT_IsSpace(int c);

/*	@	ctype.h > isdigit()
**	Returns 1 if the given char 'c' is a numerical digit,
**	and returns 0 otherwise.
*/
int		FT_IsDigit(int c);

/*	@	ctype.h > isprint()
**	Returns 1 if the given char 'c' is a hexadecimal character
**	(either 0-9 or  A-F lowercase or uppercase), and returns 0 otherwise.
*/
int		FT_IsHexDigit(int c);

/*	@	ctype.h > ispunct()
**	Returns 1 if the given char 'c' is a printable ASCII character,
**	and returns 0 otherwise.
*/
int		FT_IsPunctuation(int c);

/*	@	ctype.h > isprint()
**	Returns 1 if the given char 'c' is a printable ASCII character,
**	and returns 0 otherwise.
*/
int		FT_IsPrintable(int c);

/*	@	ctype.h > isascii()
**	Returns 1 if the given char 'c' has a value between 0 and 127,
**	and returns 0 otherwise.
*/
int		FT_IsASCII(int c);



/* ************************************************************************** */
/*                           Character Substitutions                          */
/* ************************************************************************** */

/*	@	ctype.h > toupper()
**	Returns the uppercase equivalent of the given character 'c'
**	(nothing is done if 'c' is not a letter character).
*/
int		FT_ToUppercase(int c);

/*	@	ctype.h > tolower()
**	Returns the lowercase equivalent of the given character 'c'
**	(nothing is done if 'c' is not a letter character).
*/
int		FT_ToLowercase(int c);

#endif
