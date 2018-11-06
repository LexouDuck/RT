/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>

/* ************************************************************************** */
/*                                  Macros                                    */
/* ************************************************************************** */

/*
**	Define the common useful macros for writing some pseudo-boolean syntax.
*/
# define FALSE	0
# define TRUE	1

/*
**	Define some useful string literals for some common number bases.
**	Should be used with FT_ConvertToNumber_Base() & FT_ConvertToString_Base()
*/
# ifndef __BASES__
#  define __BASES__
#  define BINARY	"01"
#  define OCTAL		"01234567"
#  define DECIMAL	"0123456789"
#  define HEX_LOWER	"0123456789abcdef"
#  define HEX_UPPER	"0123456789ABCDEF"
# endif

/*
**	TODO tristan explain this
*/
# define _FLOAT_64_



/* ************************************************************************** */
/*                      Shorthands for primitive types                        */
/* ************************************************************************** */

/*
**	Define pseudo-types for all the primitive number types in a clear naming
**	convention, to better reflect the amount of bits used by each type.
**	(and also to avoid having to type 'unsigned' all the time)
*/
typedef unsigned char	t_u8;
typedef unsigned short	t_u16;
typedef unsigned int	t_u32;
typedef	unsigned long	t_u64;

typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;

typedef float			t_f32;
typedef double			t_f64;

/*
**	TODO tristan explain this
*/
typedef t_f64			t_float;

/*
**	Define a boolean pseudo-type that is potentially faster than just 'int'.
**	The uint_fast8_t type is the fastest primitive type on the current machine
**	which contains at least 8 usable bits (so a range of -128/127 or 0/255).
**	On ARM processors this type might be 'int', otherwise it might be 'char'.
**	On embedded systems, this type could have all sorts of unusual bitsizes.
*/
typedef uint_fast8_t	t_bool;



/* ************************************************************************** */
/*                       Variable-size primitive types                        */
/* ************************************************************************** */

/*
**	These unions are used for certain difficult casting conditions.
**	TODO tristan explain exactly where its used and how
*/
typedef union			u_varint
{
	t_s8			sc;
	t_s16			ss;
	t_s32			si;
	t_s64			sl;
	t_u8			uc;
	t_u16			us;
	t_u32			ui;
	t_u64			ul;
}						t_varint;

typedef union			u_varfloat
{
	t_f32			f;
	t_f64			lf;
}						t_varfloat;

#endif
