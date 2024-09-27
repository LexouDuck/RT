/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 23:00:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/18 18:13:23 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			mat44_app_vec3(t_vec_3d result,
								t_mat_4b4 const mat,
								t_vec_3d const v)
{
	t_vec_4d	tmp;

	mat44_app_vec(tmp, mat, (t_vec_4d){v[0], v[1], v[2], 1.});
	vec3_cpy(result, tmp);
}

t_ray			ray_x_to_y(t_mat_4b4 const x_to_y,
						t_mat_3b3 linear_x_to_y, t_ray const ray)
{
	t_ray		result;

	mat44_app_vec3(result.pos, x_to_y, ray.pos);
	mat33_app_vec(result.dir, linear_x_to_y, ray.dir);
	result.t = ray.t;
	return (result);
}

t_bool			trace_ray_to_objs(t_control *ctrl, t_ray ray,
									t_object *hit_obj, t_ray *res_objray)
{
	t_bool		has_inter;
	t_ray		objray;
	int			k;
	t_object	cur_obj;

	k = -1;
	has_inter = FALSE;
	while (++k < ctrl->objlst_len)
	{
		cur_obj = ctrl->objlst[k];
		objray = ray_x_to_y(cur_obj.w_to_o, cur_obj.linear_w_to_o, ray);
		if (cur_obj.intersect(&objray))
		{
			if (objray.t < ray.t)
			{
				has_inter = TRUE;
				ray.t = objray.t;
				if (hit_obj)
					*hit_obj = ctrl->objlst[k];
				if (res_objray)
					*res_objray = objray;
			}
		}
	}
	return (has_inter);
}

/*
** Rays are defined in Cam Space then sent to World Space.
**
** Intersections should be tested for in world space. Note that since there is
** no translation on it, as all rays start at (0., 0., 0.) in cam space,
** ray.dir can be normalized after c_to_w, rather than normalizing before and
** building a "unit_c_to_w" matrix.
*/

void			cast_rays(t_control *ctrl)
{
	int			i;
	int			j;
	t_ray		ray;
	t_float		fov_val;
	t_object	hit_obj;

	fov_val = -REN_W / (2 * tan(ctrl->cam.hrz_fov));
	i = -1;
	while (++i < REN_H)
	{
		j = -1;
		while (++j < REN_W)
		{
			vec3_cpy(ray.pos, ctrl->cam.world_pos);
			ray.t = ctrl->render_dist;
			vec3_set(ray.dir, j - REN_W / 2, i - REN_H / 2, fov_val);
			mat44_app_vec3(ray.dir, ctrl->cam.c_to_w, ray.dir);
			vec3_eucl_nrmlz(ray.dir, ray.dir);
			if (trace_ray_to_objs(ctrl, ray, &hit_obj, &ray))
				((t_u32 *)ctrl->img_data)[i * REN_W + j] =
					get_color_from_fixed_objray(ctrl, hit_obj, ray);
		}
	}
}
