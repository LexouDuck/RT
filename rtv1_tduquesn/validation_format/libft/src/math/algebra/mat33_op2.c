/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat33_op2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 10:10:53 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/09 15:13:19 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

/*
**	[ 0  3  6 ]
**  [ 1  4  7 ]
**  [ 2  5  8 ]
*/

t_float			mat33_det(t_mat_3b3 const m)
{
	return (m[0] * m[4] * m[8] + m[1] * m[5] * m[6] + m[2] * m[3] * m[7]
			- m[2] * m[4] * m[6] - m[1] * m[3] * m[8] - m[0] * m[5] * m[7]);
}

/*
** M^-1 = 1/det * adj(m) and adj(m) = comat(m^transpose)
*/

void			mat33_inv(t_mat_3b3 result, t_mat_3b3 const m)
{
	t_float		det;
	t_mat_3b3	tmp;

	if ((det = mat33_det(m)) == 0.)
	{
		write(2, "mat33_inv: non invertible matrix error\n", 28);
		ft_bzero(result, T_MAT33_SIZE);
		return ;
	}
	tmp[0] = m[4] * m[8] - m[5] * m[7];
	tmp[3] = m[5] * m[6] - m[3] * m[8];
	tmp[6] = m[3] * m[7] - m[4] * m[6];
	tmp[1] = m[2] * m[7] - m[1] * m[8];
	tmp[4] = m[0] * m[8] - m[2] * m[6];
	tmp[7] = m[1] * m[6] - m[0] * m[7];
	tmp[2] = m[1] * m[5] - m[2] * m[4];
	tmp[5] = m[2] * m[3] - m[0] * m[5];
	tmp[8] = m[0] * m[4] - m[1] * m[3];
	ft_memcpy(result, tmp, sizeof(tmp));
	mat33_scale(result, 1. / det, result);
}
