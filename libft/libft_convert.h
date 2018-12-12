/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_convert.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERT_H
# define LIBFT_CONVERT_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

#define	N8_MAXDIGIT		3
#define	N16_MAXDIGIT	5
#define	N32_MAXDIGIT	10
#define	N64_MAXDIGIT	20

#define	F32_MAXDIGIT	10
#define	F64_MAXDIGIT	20

/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

char*	ft_s8_to_str(t_s8 n);
char*	ft_s16_to_str(t_s16 n);
char*	ft_s32_to_str(t_s32 n);
char*	ft_s64_to_str(t_s64 n);

char*	ft_u8_to_str(t_u8 n);
char*	ft_u16_to_str(t_u16 n);
char*	ft_u32_to_str(t_u32 n);
char*	ft_u64_to_str(t_u64 n);

char*	ft_f32_to_str(t_f32 n, t_u8 precision);
char*	ft_f64_to_str(t_f64 n, t_u8 precision);



t_s8	ft_str_to_s8(char *str);
t_s16	ft_str_to_s16(char *str);
t_s32	ft_str_to_s32(char *str);
t_s64	ft_str_to_s64(char *str);

t_u8	ft_str_to_u8(char *str);
t_u16	ft_str_to_u16(char *str);
t_u32	ft_str_to_u32(char *str);
t_u64	ft_str_to_u64(char *str);

t_f32	ft_str_to_f32(char *str);
t_f64	ft_str_to_f64(char *str);

/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

char*	ft_u8_to_hex(t_u8 n);
char*	ft_u16_to_hex(t_u16 n);
char*	ft_u32_to_hex(t_u32 n);
char*	ft_u64_to_hex(t_u64 n);

t_u8	ft_hex_to_u8(char *str);
t_u16	ft_hex_to_u16(char *str);
t_u32	ft_hex_to_u32(char *str);
t_u64	ft_hex_to_u64(char *str);

/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

char*	ft_s8_to_strbase(t_s8 n, char *base);
char*	ft_s16_to_strbase(t_s16 n, char *base);
char*	ft_s32_to_strbase(t_s32 n, char *base);
char*	ft_s64_to_strbase(t_s64 n, char *base);

char*	ft_u8_to_strbase(t_u8 n, char *base);
char*	ft_u16_to_strbase(t_u16 n, char *base);
char*	ft_u32_to_strbase(t_u32 n, char *base);
char*	ft_u64_to_strbase(t_u64 n, char *base);



t_s8	ft_strbase_to_s8(char *str, char *base);
t_s16	ft_strbase_to_s16(char *str, char *base);
t_s32	ft_strbase_to_s32(char *str, char *base);
t_s64	ft_strbase_to_s64(char *str, char *base);

t_u8	ft_strbase_to_u8(char *str, char *base);
t_u16	ft_strbase_to_u16(char *str, char *base);
t_u32	ft_strbase_to_u32(char *str, char *base);
t_u64	ft_strbase_to_u64(char *str, char *base);

/*
** ************************************************************************** *|
**                         Other Conversion Functions                         *|
** ************************************************************************** *|
*/

char*	ft_bool_to_str(t_bool value);
t_bool	ft_str_to_bool(char *str);

#endif
