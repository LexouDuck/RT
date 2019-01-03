/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u64bits_itoj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 04:18:06 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:14:49 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"

/*
** Returns a value such that every bit b that is not at index i <= b < j is
** switched off. Returns -1 (ie, 0xFFF...FF) in case of error.
** TODO: add to libft_mem.h and appropriate doc
** TODO: make it work with a byte_len argument 1, 2, 4 or 8, like ft_swap ?
*/
/*
** 0 is MSB, 63 is LSB ; bit at i included, bit at j excluded
** j is an index, not a number of bits after i.
*/
/*
** 12 bits, i = 1; j = 8
** 101011010111		input
** 1_0101101_0111	output, left and right parts are turned to 0.
** \ is overwritten, _ is added :
** <<  => 1\010110101011_0		i = 1
** >>  => 00000_0101101\01011	bitnb + i - j = 12 + 1 - 8 = 5
** <<  => 0000\00101101_0000	bitnb - j = 4
** ==  => 0_0101101_0000
*/

t_u64			ft_u64bits_itoj(t_u64 ul, t_u8 i, t_u8 j)
{
	t_u64	bits;

	if (63 < i || 64 < j || j < i)
		return (_ALLBITS_);
	bits = ((_ALLBITS_ << i) >> (64 + i - j)) << (64 - j);
	return (ul & bits);
}
