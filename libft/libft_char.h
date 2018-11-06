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

/*
** Returns 1 if the given char 'c' is a letter (lowercase or uppercase),
** and returns 0 otherwise.
*/
int		FT_IsAlpha(int c);

/*
** Returns 1 if the given char 'c' is a numerical digit,
** and returns 0 otherwise.
*/
int		FT_IsDigit(int c);

/*
** Returns 1 if the given char 'c' is alphanumeric (number or letter),
** and returns 0 otherwise.
*/
int		FT_IsAlphanumeric(int c);

/*
** Returns 1 if the given char 'c' has a value between 0 and 127,
** and returns 0 otherwise.
*/
int		FT_IsASCII(int c);

/*
** Returns 1 if the given char 'c' is a printable ASCII character,
** and returns 0 otherwise.
*/
int		FT_IsPrint(int c);

/*
** Returns 1 if the given char 'c' is whitespace character: \r,\n,\f,\v,\t,' '
** (carriage return, newline, form feed, vertical tab, tab, or space),
** and returns 0 otherwise.
*/
int		FT_IsSpace(int c);



/* ************************************************************************** */
/*                           Character Substitutions                          */
/* ************************************************************************** */

/*
** Returns the uppercase equivalent of the given character 'c'
** (nothing is done if 'c' is not a letter character).
*/
int		FT_ToUppercase(int c);
/*
** Returns the lowercase equivalent of the given character 'c'
** (nothing is done if 'c' is not a letter character).
*/
int		FT_ToLowercase(int c);

#endif
