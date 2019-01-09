/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 23:00:36 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/09 14:51:30 by fulguritu        ###   ########.fr       */
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
						t_mat_3b3 const linear_x_to_y,
						t_ray const ray)
{
	t_ray		result;

	mat44_app_vec3(result.pos, x_to_y, ray.pos);
	mat33_app_vec(result.dir, linear_x_to_y, ray.dir);
	vec3_eucl_nrmlz(result.dir, result.dir);
	result.t = ray.t;
	result.depth = ray.depth;
	return (result);
}

/*
** The normal and in_ray.dir  should be set.
*/

inline void		get_reflect(t_shader *shdr)
{
	vec3_scale(shdr->out_ray.dir,
		-2 * vec3_dot(shdr->in_ray.dir, shdr->normal), shdr->normal);
	vec3_add(shdr->out_ray.dir, shdr->out_ray.dir, shdr->in_ray.dir);
}

/*
** Formula for transparency transmitted ray T:
**
** T = 	Tn + Tt
**	 = 	[n1/n2 * (I - dot(I, N) * N)]
**		+
**		[N   *   -sqrt(1 - (n1/n2)^2 * (1 - quadnorm(I, N)))]
**
** with n1 the refractive index for the incidence medium, n2 for refrac_ind of
**		the transmission medium, N the hitpos normal, I the hitpos incidence
**		vector.
**
** In shdr: in_ray, 
*/

t_bool			get_transmit(t_shader *shdr/*, t_float const refrac*/)
{
	t_float		dot_i_n;
	t_bool		incid_inside_obj;
	t_float		refrac_ratio;
	t_float		tmp;

	dot_i_n = vec3_dot(shdr->in_ray.dir, shdr->normal);
	incid_inside_obj = dot_i_n >= 0.;
	if (incid_inside_obj)
		vec3_scale(shdr->normal, -1., shdr->normal);
	refrac_ratio = incid_inside_obj ? shdr->hit_obj->refrac : 1. / shdr->hit_obj->refrac;
	if ((tmp = 1 - refrac_ratio * refrac_ratio * (1 - dot_i_n * dot_i_n)) < 0.)
		return (FALSE);
//	Tn
	vec3_displace(shdr->in_ray.dir, -dot_i_n, shdr->normal);
	vec3_scale(shdr->out_ray.dir, refrac_ratio, shdr->in_ray.dir);
//	+ Tt
	vec3_displace(shdr->out_ray.dir, -sqrt(tmp), shdr->normal);
//	Position correction for transmission
	vec3_displace(shdr->out_ray.pos, -APPROX, shdr->normal);
	return (TRUE);
}


t_vcolor					resolve_intersection(t_control *ctrl,
									t_ray const incident,
									t_object *hit_obj)
{
	//!!before calling any trace, put rays back into world space and their direction normalized
	
	t_shader		shdr;
	t_vcolor		res;
	t_material		mater;

	if ((shdr.out_ray.depth = incident.depth + 1) < MAX_RAY_DEPTH)
	{
		res.val = (t_rgb){0., 0., 0.};
		return (res);
	}
	shdr.in_ray = incident;
	shdr.hit_obj = hit_obj;
	mater = hit_obj->material;
	hit_obj->get_hnn(shdr.out_ray.pos, shdr.normal, shdr.in_ray);
	shdr.out_ray.t = ctrl->render_dist;
//	shdr.out_ray.pixel = shdr.in_ray.pixel;



	if (mater == lightsrc)
	{//make it exit_error shouldn't happen here because of lst logic?
		res = get_lum_from_lightsrc(ctrl, shdr);
	}



	else if (mater == mirror)
	{	
		vec3_displace(shdr.out_ray.pos, APPROX, shdr.normal);//change if inside mirror...
		get_reflect(&shdr);
		shdr.out_ray = ray_x_to_y(shdr.hit_obj->o_to_w,
						shdr.hit_obj->linear_o_to_w, shdr.out_ray);
		vec3_eucl_nrmlz(shdr.out_ray.dir, shdr.out_ray.dir);
		res = trace_ray_to_scene(ctrl, shdr.out_ray);
	}




	else if (mater == glassy)
	{
		if (get_transmit(&shdr)) //normal should be altered to the right direction here
		{
			shdr.out_ray = ray_x_to_y(hit_obj->o_to_w, hit_obj->linear_o_to_w, shdr.out_ray);
			res = trace_ray_to_scene(ctrl, shdr.out_ray);
		}
		else
			res.val = (t_rgb){0., 0., 0.};
	}




	else if (hit_obj->material == glossy)
	{
		get_reflect(&shdr);
		vec3_displace(shdr.out_ray.pos, APPROX, shdr.normal);
		shdr.out_ray = ray_x_to_y(hit_obj->o_to_w, hit_obj->linear_o_to_w, shdr.out_ray);

		t_ray_sample	rsamp;

		rsamp = ray_sample_init_w_fixed_origin(shdr.out_ray, shdr.out_ray.dir, 5);
		vec3_cpy(res.vec, (t_vec_3d){0., 0., 0.});
		for (int i = 0; i < RAY_SAMPLE_NB; ++i)
		{
			rsamp.lum[i] = trace_ray_to_scene(ctrl, rsamp.rays[i]);
			vec3_displace(res.vec, 1. / rsamp.probs[i], rsamp.lum[i].vec);
		}
		vec3_scale(res.vec, INV_RAY_SAMPLE_NB, res.vec);
		vec3_schur(res.vec, res.vec, shdr.hit_obj->rgb.vec);
	}





	else if (hit_obj->material == diffuse)
	{	
		vec3_displace(shdr.out_ray.pos, APPROX, shdr.normal);
		mat44_app_vec3(shdr.out_ray.pos, shdr.hit_obj->o_to_w, shdr.out_ray.pos);
		mat33_app_vec(shdr.normal, shdr.hit_obj->n_to_w, shdr.normal);
		
		t_ray_sample	rsamp;
//		t_shader		lgtshdr;//necessary for specular ?

		rsamp = ray_sample_init_w_fixed_origin(shdr.out_ray, shdr.normal, 1);
		vec3_cpy(res.vec, (t_vec_3d){0., 0., 0.});
		for (int i = 0; i < RAY_SAMPLE_NB; ++i)
		{
			rsamp.lum[i] = trace_ray_to_scene(ctrl, rsamp.rays[i]);
			vec3_displace(res.vec, 1. / rsamp.probs[i], rsamp.lum[i].vec);
		}
		vec3_scale(res.vec, INV_RAY_SAMPLE_NB, res.vec);
		vec3_schur(res.vec, res.vec, shdr.hit_obj->rgb.vec);
	}

	else
		res.val = (t_rgb){0., 0., 0.};

	return (res);
}

/*
t_vcolor			color_or_secondary_ray(t_control *ctrl,
									t_ray const incident,
									t_object *hit_obj)
{
	t_vec_3d	normal;
	t_ray		reflect;
	//transmit ray is cast in a transmit subfunction
	t_ray		res_objray;
	t_color		res;

	if ((reflect.depth = incident.depth + 1) < MAX_RAY_DEPTH)
		return (BLACK);
	

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

for (int i = 0; i < MAXOUILLE; ++i)
{
		hit_obj->get_hnn(reflect.pos, normal, incident);
		vec3_randcos(reflect.dir, normal);
		vec3_scale(normal, APPROX, normal);
		vec3_add(reflect.pos, reflect.pos, normal);
		reflect.t = ctrl->render_dist;
		if (trace_ray_to_objs(ctrl, reflect, &new_hit_obj, &res_objray))
			res += color_or_secondary_ray(ctrl, res_objray, &new_hit_obj);
}
		res *= 1.0 / AMBIENT_RAY_NB *
			((0x00FF0000 & res) + (0x0000FF00 & res) + (0x000000FF & res));
	}

	return (res + get_color_from_fixed_objray(ctrl, *hit_obj, incident));
}
*/
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
	t_s32		i;
	t_s32		j;
	t_ray		ray;
	t_float		fov_val;
//	t_vcolor	reslum;


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
			ctrl->img_data[i * REN_W + j] = color_app_lum(trace_ray_to_scene(ctrl, ray));
		}
printf("%.2f / 100.00\n", (100. * (i + 1.)) / PIXEL_NB);
	}
}
