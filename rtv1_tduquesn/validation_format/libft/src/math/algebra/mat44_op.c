/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat44_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 18:58:43 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/20 18:59:08 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

void			mat44_add(t_mat_4b4 result,
							t_mat_4b4 const ma, t_mat_4b4 const mb)
{
	result[0] = ma[0] + mb[0];
	result[1] = ma[1] + mb[1];
	result[2] = ma[2] + mb[2];
	result[3] = ma[3] + mb[3];
	result[4] = ma[4] + mb[4];
	result[5] = ma[5] + mb[5];
	result[6] = ma[6] + mb[6];
	result[7] = ma[7] + mb[7];
	result[8] = ma[8] + mb[8];
	result[9] = ma[9] + mb[9];
	result[10] = ma[10] + mb[10];
	result[11] = ma[11] + mb[11];
	result[12] = ma[12] + mb[12];
	result[13] = ma[13] + mb[13];
	result[14] = ma[14] + mb[14];
	result[15] = ma[15] + mb[15];
}

void			mat44_scale(t_mat_4b4 result,
							t_float const s, t_mat_4b4 const m)
{
	result[0] = s * m[0];
	result[1] = s * m[1];
	result[2] = s * m[2];
	result[3] = s * m[3];
	result[4] = s * m[4];
	result[5] = s * m[5];
	result[6] = s * m[6];
	result[7] = s * m[7];
	result[8] = s * m[8];
	result[9] = s * m[9];
	result[10] = s * m[10];
	result[11] = s * m[11];
	result[12] = s * m[12];
	result[13] = s * m[13];
	result[14] = s * m[14];
	result[15] = s * m[15];
}

void			mat44_app_vec(t_vec_4d result,
								t_mat_4b4 const m, t_vec_4d const v)
{
	t_vec_4d	tmp;

	tmp[0] = m[0] * v[0] + m[4] * v[1] + m[8] * v[2] + m[12] * v[3];
	tmp[1] = m[1] * v[0] + m[5] * v[1] + m[9] * v[2] + m[13] * v[3];
	tmp[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
	tmp[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
	ft_memcpy(result, tmp, sizeof(tmp));
}

void			mat44_mul(t_mat_4b4 result,
							t_mat_4b4 const ma, t_mat_4b4 const mb)
{
	t_mat_4b4	tmp;

	mat44_app_vec((t_float *)tmp, ma, (t_float *)mb);
	mat44_app_vec((t_float *)tmp + 4, ma, (t_float *)mb + 4);
	mat44_app_vec((t_float *)tmp + 8, ma, (t_float *)mb + 8);
	mat44_app_vec((t_float *)tmp + 12, ma, (t_float *)mb + 12);
	ft_memcpy(result, tmp, sizeof(tmp));
}

/*
**	[ 0  4  8  12 ]
**  [ 1  5  9  13 ]
**  [ 2  6  10 14 ]
**	[ 3  7  11 15 ]
*/

void			mat44_transpose(t_mat_4b4 result, t_mat_4b4 const m)
{
	t_float		tmp[6];

	result[0] = m[0];
	result[5] = m[5];
	result[10] = m[10];
	result[15] = m[15];
	tmp[0] = m[4];
	tmp[1] = m[8];
	tmp[2] = m[12];
	tmp[3] = m[9];
	tmp[4] = m[13];
	tmp[5] = m[14];
	result[4] = m[1];
	result[8] = m[2];
	result[12] = m[3];
	result[9] = m[6];
	result[13] = m[7];
	result[14] = m[11];
	result[1] = tmp[0];
	result[2] = tmp[1];
	result[3] = tmp[2];
	result[6] = tmp[3];
	result[7] = tmp[4];
	result[11] = tmp[5];
}
