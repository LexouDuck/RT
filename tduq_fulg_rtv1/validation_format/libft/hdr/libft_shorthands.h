/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_shorthands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 00:54:52 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/20 00:54:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SHORTHANDS_H
# define LIBFT_SHORTHANDS_H

# define _FLOAT_64_

# define TRUE	1
# define FALSE	0

/*
** Shorthands for primitive types as bitsizes
*/
typedef	unsigned char	t_u8;
typedef	unsigned short	t_u16;
typedef	unsigned int	t_u32;
typedef	unsigned long	t_u64;
typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;
typedef float			t_f32;
typedef double			t_f64;
typedef t_f64			t_float;

typedef uint_fast8_t	t_bool;

/*
** Unions used for difficult casting conditions.
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
