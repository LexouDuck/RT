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

#define	MAXDIGIT_8b		3
#define	MAXDIGIT_16b	5
#define	MAXDIGIT_32b	10
#define	MAXDIGIT_64b	20

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

t_s8	ft_str_to_s8(char const *str);
t_s16	ft_str_to_s16(char const *str);
t_s32	ft_str_to_s32(char const *str);
t_s64	ft_str_to_s64(char const *str);

t_u8	ft_str_to_u8(char const *str);
t_u16	ft_str_to_u16(char const *str);
t_u32	ft_str_to_u32(char const *str);
t_u64	ft_str_to_u64(char const *str);

t_f32	ft_str_to_f32(char const *str);
t_f64	ft_str_to_f64(char const *str);

/*
** ************************************************************************** *|
**                         Other Conversion Functions                         *|
** ************************************************************************** *|
*/

char*	ft_bool_to_str(t_bool value);
char*	ft_size_to_str(size_t value);

t_bool	ft_str_to_bool(char const *str);
size_t	ft_str_to_size(char const *str);

/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

char*	ft_u8_to_hex(t_u8 n);
char*	ft_u16_to_hex(t_u16 n);
char*	ft_u32_to_hex(t_u32 n);
char*	ft_u64_to_hex(t_u64 n);

t_u8	ft_hex_to_u8(char const *str);
t_u16	ft_hex_to_u16(char const *str);
t_u32	ft_hex_to_u32(char const *str);
t_u64	ft_hex_to_u64(char const *str);

/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

char*	ft_s8_to_strbase(t_s8 n, char const *base);
char*	ft_s16_to_strbase(t_s16 n, char const *base);
char*	ft_s32_to_strbase(t_s32 n, char const *base);
char*	ft_s64_to_strbase(t_s64 n, char const *base);

char*	ft_u8_to_strbase(t_u8 n, char const *base);
char*	ft_u16_to_strbase(t_u16 n, char const *base);
char*	ft_u32_to_strbase(t_u32 n, char const *base);
char*	ft_u64_to_strbase(t_u64 n, char const *base);

t_s8	ft_strbase_to_s8(char const *str, char const *base);
t_s16	ft_strbase_to_s16(char const *str, char const *base);
t_s32	ft_strbase_to_s32(char const *str, char const *base);
t_s64	ft_strbase_to_s64(char const *str, char const *base);

t_u8	ft_strbase_to_u8(char const *str, char const *base);
t_u16	ft_strbase_to_u16(char const *str, char const *base);
t_u32	ft_strbase_to_u32(char const *str, char const *base);
t_u64	ft_strbase_to_u64(char const *str, char const *base);

#endif
