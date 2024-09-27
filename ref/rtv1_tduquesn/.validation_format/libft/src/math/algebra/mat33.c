/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat33.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 02:12:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/01 10:14:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

void			mat33_set(t_mat_3b3 result, t_vec_3d const v0,
							t_vec_3d const v1, t_vec_3d const v2)
{
	result[0] = v0[0];
	result[1] = v0[1];
	result[2] = v0[2];
	result[3] = v1[0];
	result[4] = v1[1];
	result[5] = v1[2];
	result[6] = v2[0];
	result[7] = v2[1];
	result[8] = v2[2];
}

void			mat33_cpy(t_mat_3b3 result, t_mat_3b3 const mat)
{
	result[0] = mat[0];
	result[1] = mat[1];
	result[2] = mat[2];
	result[3] = mat[3];
	result[4] = mat[4];
	result[5] = mat[5];
	result[6] = mat[6];
	result[7] = mat[7];
	result[8] = mat[8];
}

void			mat33_rot(t_mat_3b3 result, t_float theta, int_fast8_t axis)
{
	t_float		c_th;
	t_float		s_th;

	if (axis < 0 || axis > 2)
		write(2, "mat33_rot: axis is not coherent with 3D...", 43);
	c_th = cosf(theta);
	s_th = sinf(theta);
	if (axis == 0)
		mat33_set(result, (t_vec_3d){1., 0., 0.},
						(t_vec_3d){0., c_th, s_th},
						(t_vec_3d){0., -s_th, c_th});
	else if (axis == 1)
		mat33_set(result, (t_vec_3d){c_th, 0., -s_th},
						(t_vec_3d){0., 1., 0.},
						(t_vec_3d){s_th, 0., c_th});
	else
		mat33_set(result, (t_vec_3d){c_th, s_th, 0.},
						(t_vec_3d){-s_th, c_th, 0.},
						(t_vec_3d){0., 0., 1.});
}

void			mat33_set_diagmat(t_mat_3b3 result, t_vec_3d const coefs)
{
	ft_bzero(result, T_MAT33_SIZE);
	result[0] = coefs[0];
	result[4] = coefs[1];
	result[8] = coefs[2];
}
