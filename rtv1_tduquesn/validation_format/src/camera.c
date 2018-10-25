/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 00:31:44 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/05 07:44:51 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		cam_build_matrices(t_camera *cam)
{
	t_mat_3b3	tmp;
	t_vec_3d	v;
	t_mat_4b4	result;

	mat33_set(tmp, cam->axis_x, cam->axis_y, cam->axis_z);
	result[0] = tmp[0];
	result[1] = tmp[1];
	result[2] = tmp[2];
	result[3] = 0.;
	result[4] = tmp[3];
	result[5] = tmp[4];
	result[6] = tmp[5];
	result[7] = 0.;
	result[8] = tmp[6];
	result[9] = tmp[7];
	result[10] = tmp[8];
	result[11] = 0.;
	vec3_cpy(v, cam->world_pos);
	result[12] = v[0];
	result[13] = v[1];
	result[14] = v[2];
	result[15] = 1.;
	ft_memcpy(cam->c_to_w, result, T_MAT44_SIZE);
	mat44_inv(result, result);
	ft_memcpy(cam->w_to_c, result, T_MAT44_SIZE);
}

t_camera		init_cam(t_vec_3d polar_cam_pos, t_vec_3d anchor,
						t_float fov)
{
	t_camera	result;

	vec3_cpy(result.anchor, anchor);
	vec3_cpy(result.polar_pos, polar_cam_pos);
	vec3_polar_to_cartesian(result.reltv_pos, polar_cam_pos);
	vec3_add(result.world_pos, result.reltv_pos, result.anchor);
	vec3_cpy(result.axis_z, result.reltv_pos);
	vec3_eucl_nrmlz(result.axis_z, result.axis_z);
	vec3_set(result.axis_y, 0., 1., 0.);
	vec3_cross(result.axis_x, result.axis_y, result.axis_z);
	vec3_eucl_nrmlz(result.axis_x, result.axis_x);
	vec3_cross(result.axis_y, result.axis_x, result.axis_z);
	result.hrz_fov = fov;
	cam_build_matrices(&result);
	return (result);
}
