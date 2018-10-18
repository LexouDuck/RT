/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:16:11 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/09 15:15:02 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

void			vec3_add(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2)
{
	result[0] = v1[0] + v2[0];
	result[1] = v1[1] + v2[1];
	result[2] = v1[2] + v2[2];
}

void			vec3_sub(t_vec_3d result, t_vec_3d const v1, t_vec_3d const v2)
{
	result[0] = v1[0] - v2[0];
	result[1] = v1[1] - v2[1];
	result[2] = v1[2] - v2[2];
}

void			vec3_scale(t_vec_3d result, t_float const s, t_vec_3d const v)
{
	result[0] = s * v[0];
	result[1] = s * v[1];
	result[2] = s * v[2];
}

inline t_float	vec3_dot(t_vec_3d const v1, t_vec_3d const v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

void			vec3_cross(t_vec_3d result,
							t_vec_3d const v1, t_vec_3d const v2)
{
	t_vec_3d tmp;

	tmp[0] = v1[1] * v2[2] - v1[2] * v2[1];
	tmp[1] = v1[2] * v2[0] - v1[0] * v2[2];
	tmp[2] = v1[0] * v2[1] - v1[1] * v2[0];
	result[0] = tmp[0];
	result[1] = tmp[1];
	result[2] = tmp[2];
}
