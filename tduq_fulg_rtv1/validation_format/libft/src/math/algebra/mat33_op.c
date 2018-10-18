/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat33_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 18:58:43 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/20 18:59:08 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

void			mat33_add(t_mat_3b3 result,
							t_mat_3b3 const ma, t_mat_3b3 const mb)
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
}

void			mat33_scale(t_mat_3b3 result,
							t_float const s, t_mat_3b3 const m)
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
}

void			mat33_app_vec(t_vec_3d result,
								t_mat_3b3 const m, t_vec_3d const v)
{
	t_mat_3b3	tmp;

	tmp[0] = m[0] * v[0] + m[3] * v[1] + m[6] * v[2];
	tmp[1] = m[1] * v[0] + m[4] * v[1] + m[7] * v[2];
	tmp[2] = m[2] * v[0] + m[5] * v[1] + m[8] * v[2];
	result[0] = tmp[0];
	result[1] = tmp[1];
	result[2] = tmp[2];
}

void			mat33_mul(t_mat_3b3 result,
							t_mat_3b3 const ma, t_mat_3b3 const mb)
{
	t_mat_3b3	tmp;

	mat33_app_vec((t_float *)tmp, ma, (t_float *)mb);
	mat33_app_vec((t_float *)tmp + 3, ma, (t_float *)mb + 3);
	mat33_app_vec((t_float *)tmp + 6, ma, (t_float *)mb + 6);
	ft_memcpy(result, tmp, sizeof(tmp));
}

void			mat33_transpose(t_mat_3b3 result, t_mat_3b3 const src)
{
	t_float		tmp;

	tmp = src[1];
	result[1] = src[3];
	result[3] = tmp;
	tmp = src[2];
	result[2] = src[6];
	result[6] = tmp;
	tmp = src[7];
	result[7] = src[5];
	result[5] = tmp;
	result[0] = src[0];
	result[4] = src[4];
	result[8] = src[8];
}
