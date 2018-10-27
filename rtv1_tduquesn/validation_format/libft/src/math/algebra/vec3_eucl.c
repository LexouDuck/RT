/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_eucl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 02:13:00 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/17 00:07:35 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

inline t_float	vec3_eucl_norm(t_vec_3d const v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

inline t_float	vec3_eucl_quadnorm(t_vec_3d const v)
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void			vec3_eucl_nrmlz(t_vec_3d result, t_vec_3d const v)
{
	t_float		inv_norm;

	inv_norm = 1. / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	result[0] = inv_norm * v[0];
	result[1] = inv_norm * v[1];
	result[2] = inv_norm * v[2];
}

t_float			vec3_eucl_dist(t_vec_3d const v1, t_vec_3d const v2)
{
	t_vec_3d		tmp;

	vec3_sub(tmp, v1, v2);
	return (vec3_eucl_norm(tmp));
}

t_float			vec3_eucl_quaddist(t_vec_3d const v1, t_vec_3d const v2)
{
	t_vec_3d		tmp;

	vec3_sub(tmp, v1, v2);
	return (vec3_eucl_quadnorm(tmp));
}
