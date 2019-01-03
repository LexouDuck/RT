/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:45:43 by tduquesn          #+#    #+#             */
/*   Updated: 2018/03/07 19:32:38 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** TODO
** Fix strlspad,
** add boolean functions (bool and boolarr)
** strinsert is an inplace which returns itself: make other inplace functions
** 				like this ?
** lstinsert
** lstpop with pointers ? and rename current lstpop to lstpopi ?
** add ft_puthex_llstelem to libft, maybe rename putlst_hex
** vim -c  sed \ti++; to \t++i;
** vim -c  sed base_n to radix;
** rename all llst to lst
** Fix libft main.
** make a t_uple type with pragmas to dynamically define type.
** make an optimized Tensor/Matrix/Vector library.
*/

# define OK 0
# define ERROR 1

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <inttypes.h>
# include <limits.h>
# include "libft_shorthands.h"

# ifndef __BASES__
#  define __BASES__
#  define BINAR "01"
#  define OCTAL "01234567"
#  define DECIM "0123456789"
#  define HXLOW "0123456789abcdef"
#  define HXUPP "0123456789ABCDEF"
# endif

/*
** NB : The functions below are kept in libft.h until they have been properly
** debugged. Their source should be kept in the top-level of ../src/
*/

char		*ft_str_base_to_base_expn(char const *str, char const *base_f,
									char const *base_t, t_u32 expn);

char		*ft_str_base_expn_to_base(char const *str, char const *base_f,
									char const *base_t, t_u32 expn);

#endif
