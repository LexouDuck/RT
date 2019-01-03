/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 23:00:36 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/03 17:36:57 by fulguritu        ###   ########.fr       */
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
	result.depth = ray.depth;
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
** Formula for transparency transmitted ray T:
**
** T = Tn + Tt
**	 = [n1/n2 * (I - dot(I, N) N)] + [-N * sqrt(1 - (n1/n2)^2 * (1 - quadnorm(I, Ni)))]
**
** with n1 the refractive index for the incidence medium, n2 for refrac_ind of
**		the transmission medium, N the hitpos normal, I the hitpos incidence
**		vector.
*/

t_bool			get_transmit(t_vec_3d result, t_vec_3d const incident,
								t_vec_3d normal, t_float const refrac)
{
	t_float		dot_i_n;
	t_bool		incid_inside_obj;
	t_float		refrac_ratio;
	t_float		tmp;
	t_vec_3d	transmit_n;

	dot_i_n = vec3_dot(incident, normal);
	incid_inside_obj = dot_i_n >= 0.;
	if (incid_inside_obj)
		vec3_scale(normal, -1., normal);
	refrac_ratio = incid_inside_obj ? refrac : 1. / refrac;
	if ((tmp = 1 - refrac_ratio * refrac_ratio * (1 - dot_i_n * dot_i_n)) < 0.)
		return (FALSE);
	vec3_scale(result, -dot_i_n, normal);
	vec3_add(result, result, incident);
	vec3_scale(result, refrac_ratio, result);
	vec3_scale(transmit_n, -sqrt(tmp), normal);
	vec3_add(result, result, transmit_n);
	return (TRUE);
}

t_color			color_or_secondary_ray(t_control *ctrl,
									t_ray const incident,
									t_object *hit_obj)
{
	t_vec_3d	normal;
	t_ray		reflect;
	t_ray		res_objray;
	t_color		res;

	if (hit_obj->material == mirror &&
		(reflect.depth = incident.depth + 1) < MAX_RAY_DEPTH)
	{
		hit_obj->get_hnn(reflect.pos, normal, incident);
		get_reflect(reflect.dir, incident.dir, normal);
		vec3_scale(normal, APPROX, normal);
		vec3_add(reflect.pos, reflect.pos, normal);
		reflect.t = ctrl->render_dist;
		reflect = ray_x_to_y(hit_obj->o_to_w, hit_obj->linear_o_to_w, reflect);
		trace_ray_to_objs(ctrl, reflect, hit_obj, &res_objray);
		return (color_or_secondary_ray(ctrl, res_objray, hit_obj));
	}

	if (hit_obj->material == glassy &&
		(reflect.depth = incident.depth + 1) < MAX_RAY_DEPTH)
	{//for now we call "reflect" the "transmitted" ray
		hit_obj->get_hnn(reflect.pos, normal, incident);
		if (get_transmit(reflect.dir, incident.dir, normal, hit_obj->refrac)) //normal should be altered to the right direction here
		{
			vec3_scale(normal, -APPROX, normal);
			vec3_add(reflect.pos, reflect.pos, normal);
			reflect.t = ctrl->render_dist;
			trace_ray_to_objs(ctrl, reflect, hit_obj, &res_objray);
			return (color_or_secondary_ray(ctrl, res_objray, hit_obj));
		}
	}


	res = 0;
	//rand dir is first defined in local space
	if (hit_obj->material == diffuse && ctrl->show_ambient &&
		(reflect.depth = incident.depth + 1) < MAX_RAY_DEPTH)
	{
		if (reflect.depth < MAX_RAY_DEPTH - 2)
			reflect.depth = MAX_RAY_DEPTH - 2;

int MAXOUILLE = reflect.depth == MAX_RAY_DEPTH - 2 ? AMBIENT_RAY_NB : 4;

for (int i = 0; i < MAXOUILLE; ++i)
{
		t_float		t1 = ft_frand_0_to_1();
		t_float		t2 = ft_frand_0_to_1();
		t_float		tmp;
		t_vec_3d	randdir;
		t_vec_3d	randv;
		t_vec_3d	vtan1;
		t_vec_3d	vtan2;
		t_object	new_hit_obj;


		hit_obj->get_hnn(reflect.pos, normal, incident);
		tmp = sqrt(1. - t2);
		t1 = TAU * t1;
		vec3_set(randdir, cos(t1) * tmp, sin(t1) * tmp, sqrt(t2));
		vec3_set(randv, ft_frand_0_to_1() - 0.5, ft_frand_0_to_1() - 0.5, ft_frand_0_to_1() - 0.5);
		vec3_cross(vtan1, normal, randv);
		vec3_eucl_nrmlz(vtan1, vtan1);
		vec3_cross(vtan2, vtan1, normal);
		vec3_set(randdir,
		randdir[0] * vtan1[0] + randdir[1] * vtan2[0] + randdir[2] * normal[0], 
		randdir[0] * vtan1[1] + randdir[1] * vtan2[1] + randdir[2] * normal[1],
		randdir[0] * vtan1[2] + randdir[1] * vtan2[2] + randdir[2] * normal[2]);		
		vec3_scale(normal, APPROX, normal);
		vec3_add(reflect.pos, reflect.pos, normal);
		vec3_cpy(reflect.dir, randdir);
		reflect.t = ctrl->render_dist;
		if (trace_ray_to_objs(ctrl, reflect, &new_hit_obj, &res_objray))
			res += color_or_secondary_ray(ctrl, res_objray, &new_hit_obj);
}
		res *= 1.0 / AMBIENT_RAY_NB *
			((0x00FF0000 & res) + (0x0000FF00 & res) + (0x000000FF & res));
	}

	return (res + get_color_from_fixed_objray(ctrl, *hit_obj, incident));
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
			ray.depth = 0;
			vec3_set(ray.dir, j - REN_W / 2, i - REN_H / 2, fov_val);
			mat44_app_vec3(ray.dir, ctrl->cam.c_to_w, ray.dir);
			vec3_eucl_nrmlz(ray.dir, ray.dir);
			if (trace_ray_to_objs(ctrl, ray, &hit_obj, &ray))
				((t_u32 *)ctrl->img_data)[i * REN_W + j] = 
					color_or_secondary_ray(ctrl, ray, &hit_obj);
		}
	}
}
