/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_get_greatest_sub_pow10.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:37:24 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

/*
** En gros: tu fais ton uitoa en commençant par le most significant digit.
** Comment faire pour un bigint ? Tu trouves la puissance de 10 juste en
** dessous.
**
** Le procédé c'est en gros ça:
** => log2(nb) = exp_base_2
** => log10(nb) = exp_base_10
** (noter que "base" c'est au sens de "base" d'une exponentielle ou d'un
** logarithme, pas de "base numérique")
** => nb * 2^eb2 = nb * 10^eb10   <=>   eb2*ln(2) = eb10*ln(10)
** => donc eb10 = eb2 * ln(2) / ln(10)
**
** Disons qu'on tombe sur eb10 = 225.54343......
** Il y a 226 digits en base 10 pour notre nombre.
** Soit tu fais 225 multiplications de vlq pour trouver ta puissance de 10 juste
**  en dessous.
** Soit t'es malin, tu remarques que 10^225 = 10^(128 + 64 + 32 + 1)
**											= 10^128 * 10^64 * 10^32 * 10
** Et tu gardes en déjà calculé tes vlq contenant 10 ^ pow_of_2 jusqu'à la
** limite des float représentables (ici, 10^330 si je me souviens bien, donc
** on n'a que besoin de 10^256 et les sous-puissances de 2)
*/
/*
** ln(2)/ln(10) in binary (approximate)
** 0.01 (MSB, so exp2 = -2[10])
** 0011 0100 0100 => 344
** 0001 0011 0101 => 135
** 0000 1001 1111 => 09F
** 0111 1001 1111 => 79F
** 1110		   => E
** => 0x1.34413509F79FEp-2
*/
/*
** Note that exp10 is the exponent if scientific decimal notation is used;
**			 exp2  is the exponent if scientific binary  notation is used;
** 		=> Both represent "their number's corresponding number of digits - 1".
*/

t_vlq		ft_vlq_get_greatest_sub_pow10(t_vlq vlq)
{
	t_u32			exp2;
	t_u32			exp10;

	if (vlq[0] < 10)
		return (0);
	exp2 = ft_vlq_count_sigbit(vlq) - 1;
	exp10 = ft_floor(LN2_DIV_LN10 * exp2);
	return (ft_vlq_getpow10(exp10));
}
