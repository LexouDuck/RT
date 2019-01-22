/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:28:40 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/21 18:13:38 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				vec3_schur(t_vec_3d res,
								t_vec_3d const v1,
								t_vec_3d const v2)
{
	res[0] = v1[0] * v2[0];
	res[1] = v1[1] * v2[1];
	res[2] = v1[2] * v2[2];
}

void				vec3_displace(t_vec_3d edit,
									t_float const coef,
									t_vec_3d const dir)
{
	t_vec_3d	scaled_dir;

	vec3_scale(scaled_dir, coef, dir);
	vec3_add(edit, edit, scaled_dir);
}

void				mat44_app_vec3(t_vec_3d result,
									t_mat_4b4 const mat,
									t_vec_3d const v)
{
	t_vec_4d	tmp;

	mat44_app_vec(tmp, mat, (t_vec_4d){v[0], v[1], v[2], 1.});
	vec3_cpy(result, tmp);
}
