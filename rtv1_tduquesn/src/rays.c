/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 23:00:36 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/21 05:48:43 by fulguritu        ###   ########.fr       */
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
	result.sray_depth = ray.sray_depth;
	return (result);
}



/*
** The normal and in_ray.dir  should be set.
*/

inline void		shader_get_reflect(t_shader *shdr)
{
	vec3_scale(shdr->out_ray_os.dir,
		-2 * vec3_dot(shdr->in_ray.dir, shdr->normal_os), shdr->normal_os);
	vec3_add(shdr->out_ray_os.dir, shdr->out_ray_os.dir, shdr->in_ray.dir);
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

t_bool			shader_get_transmit(t_shader *shdr)
{
	t_float		dot_i_n;
	t_bool		incid_inside_obj;
	t_float		refrac_ratio;
	t_float		tmp;

	dot_i_n = vec3_dot(shdr->in_ray.dir, shdr->normal_os);
	incid_inside_obj = dot_i_n >= 0.;
	if (incid_inside_obj)
		vec3_scale(shdr->normal_os, -1., shdr->normal_os);
	refrac_ratio = incid_inside_obj ? shdr->hit_obj->refrac : 1. / shdr->hit_obj->refrac;
	if ((tmp = 1 - refrac_ratio * refrac_ratio * (1 - dot_i_n * dot_i_n)) < 0.)
		return (FALSE);
//	Tn
	vec3_displace(shdr->in_ray.dir, -dot_i_n, shdr->normal_os);
	vec3_scale(shdr->out_ray_os.dir, refrac_ratio, shdr->in_ray.dir);
//	+ Tt
	vec3_displace(shdr->out_ray_os.dir, -sqrt(tmp), shdr->normal_os);
//	Position correction for transmission
	vec3_displace(shdr->out_ray_os.pos, -APPROX, shdr->normal_os);
	return (TRUE);
}



t_vcolor					ray_handle_mirror(t_control *ctrl, t_shader shdr)
{
	t_vcolor	res;

//printf("mirror  ");
	vec3_displace(shdr.out_ray_os.pos, APPROX, shdr.normal_os);//TODO change if inside mirror...
	shader_get_reflect(&shdr);
	shdr.out_ray_ws = ray_x_to_y(shdr.hit_obj->o_to_w,
						shdr.hit_obj->linear_o_to_w, shdr.out_ray_os);
	res = trace_ray_to_scene(ctrl, shdr);
	vec3_schur(res.vec, res.vec, (t_vec_3d){0.9, 0.95, 0.9});//mirror blur
	return (res);
}

t_vcolor					ray_handle_glassy(t_control *ctrl, t_shader shdr)
{
	t_vcolor	res;

	if (shader_get_transmit(&shdr)) //normal should be altered to the right direction here
	{
		shdr.out_ray_ws = ray_x_to_y(shdr.hit_obj->o_to_w, shdr.hit_obj->linear_o_to_w, shdr.out_ray_os);
		//add normal to world here ?
		res = trace_ray_to_scene(ctrl, shdr);
		vec3_schur(res.vec, res.vec, (t_vec_3d){0.9, 0.95, 0.95});
	}
	else
		res.val = (t_rgb){0., 0., 0.};
	return (res);
}

t_vcolor					ray_handle_direct_lum(t_control *ctrl,
													t_shader shdr)
{
	t_object	*spot;
	t_float		quaddist;
	t_float		costh;
	t_vcolor	res;
	t_vcolor	curlum;
//	t_object	*hit_obj;

	res.val = (t_rgb){0., 0., 0.};
	for (int i = 0; i < ctrl->spotlst_len; ++i)
	{
		spot = &(ctrl->spotlst[i]);
		vec3_sub(shdr.out_ray_ws.dir, spot->pos, shdr.out_ray_ws.pos);
		quaddist = vec3_dot(shdr.out_ray_ws.dir, shdr.out_ray_ws.dir);
		shdr.out_ray_ws.t = sqrt(quaddist);
		vec3_scale(shdr.out_ray_ws.dir, 1. / shdr.out_ray_ws.t, shdr.out_ray_ws.dir);
		if (trace_ray_to_objs(ctrl, shdr.out_ray_ws, NULL, NULL))//&hit_obj, NULL) && hit_obj.material != glassy)
			continue ;
		costh = vec3_dot(shdr.normal_ws, shdr.out_ray_ws.dir);
		vec3_scale(curlum.vec,
			INV_PI * spot->intensity * ft_fmax(0., costh) / quaddist,
			shdr.hit_obj->rgb.vec);
		vec3_schur(curlum.vec, curlum.vec, spot->rgb.vec);
		vec3_add(res.vec, res.vec, curlum.vec);
	}
	return (res);
}


/*
** In this function, shdr.outray_ws must be set to be used as axis for random
** sampling.
*/
t_vcolor					ray_handle_global_lum(t_control *ctrl,
													t_shader shdr,
													int phong)
{
	t_vcolor		res;
	t_ray_sample	rsamp;

	rsamp = ray_sample_init_w_fixed_origin(shdr.out_ray_ws,
											shdr.out_ray_ws.dir, phong);
	res.val = (t_rgb){0., 0., 0.};
	for (int i = 0; i < RAY_SAMPLE_NB; ++i)
	{
		shdr.out_ray_ws = rsamp.rays[i];
		rsamp.lum[i] = trace_ray_to_scene(ctrl, shdr);
		vec3_displace(res.vec, 1. / rsamp.probs[i], rsamp.lum[i].vec);
	}
	vec3_scale(res.vec, INV_RAY_SAMPLE_NB, res.vec);
	vec3_schur(res.vec, res.vec, shdr.hit_obj->rgb.vec);
	return (res);
}

t_vcolor					ray_handle_glossy(t_control *ctrl, t_shader shdr)
{
	t_vcolor	res;
//	t_vcolor	tmp;


	vec3_displace(shdr.out_ray_os.pos, APPROX, shdr.normal_os);
	shader_get_reflect(&shdr);
	shdr.out_ray_ws = ray_x_to_y(shdr.hit_obj->o_to_w,
							shdr.hit_obj->linear_o_to_w,
							shdr.out_ray_os);
	//TODO remove ?
	res = ray_handle_direct_lum(ctrl, shdr);
/*	if (shdr.out_ray_ws.sray_depth < MAX_SAMPRAY_DEPTH)
	{
		tmp = ray_handle_globallum(ctrl, shdr, 7);
		vec3_add(res.vec, res.vec, tmp.vec);
	}
*/
	return (res);
}


t_vcolor					ray_handle_diffuse(t_control *ctrl, t_shader shdr)
{
	t_vcolor	res;
//	t_vcolor	tmp;

	vec3_displace(shdr.out_ray_os.pos, APPROX, shdr.normal_os);
	mat44_app_vec3(shdr.out_ray_ws.pos, shdr.hit_obj->o_to_w, shdr.out_ray_os.pos);	//direct lighting
	res = ray_handle_direct_lum(ctrl, shdr);
	//indirect lighting
/*	if (shdr.out_ray_ws.sray_depth < MAX_SAMPRAY_DEPTH)
	{
		tmp = ray_handle_globallum(ctrl, shdr, 1);
		vec3_add(res.vec, res.vec, tmp.vec);
	}
*/	return (res);
}


t_vcolor					resolve_intersection(t_control *ctrl,
									t_shader oldshdr,
									t_object *hit_obj,
									t_ray const incident)
{
	//!!before calling any trace, put rays back into world space and their direction normalized
	
	t_shader		shdr;
	t_vcolor		res;
	t_material		mater;

//printf("inc %d | mater %d", incident.depth, hit_obj->material);

	if ((shdr.out_ray_os.depth = incident.depth + 1) >= MAX_RAY_DEPTH)
	{
		res.val = (t_rgb){0., 0., 0.};
		return (res);
	}

	shdr.in_ray = incident;
	shdr.hit_obj = hit_obj;
	hit_obj->get_hnn(shdr.out_ray_os.pos, shdr.normal_os, shdr.in_ray);
	mat33_app_vec(shdr.normal_ws, shdr.hit_obj->n_to_w, shdr.normal_os);
	vec3_eucl_nrmlz(shdr.normal_ws, shdr.normal_ws);
	shdr.out_ray_os.t = ctrl->render_dist;
	shdr.out_ray_os.sray_depth = shdr.in_ray.sray_depth;

	mater = shdr.hit_obj->material;
	if (mater == lightsrc)
		res = get_lum_from_lightsrc(oldshdr, shdr);
	else if (mater == mirror)
		res = ray_handle_mirror(ctrl, shdr);
	else if (mater == glassy)
		res = ray_handle_glassy(ctrl, shdr);
	else if (mater == glossy)
		res = ray_handle_glossy(ctrl, shdr);
	else if (mater == diffuse)
		res = ray_handle_diffuse(ctrl, shdr);
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
	t_shader	shdr;
	t_float		fov_val;
	t_vcolor	reslum;

	fov_val = -REN_W / (2 * tan(ctrl->cam.hrz_fov));
	i = -1;
	while (++i < REN_H)
	{
		j = -1;
		while (++j < REN_W)
		{
			vec3_cpy(shdr.out_ray_ws.pos, ctrl->cam.world_pos);
			shdr.out_ray_ws.t = ctrl->render_dist;
			shdr.out_ray_ws.depth = 0;
			shdr.out_ray_ws.sray_depth = 0;
			vec3_set(shdr.out_ray_ws.dir, j - REN_W / 2, i - REN_H / 2, fov_val);
			mat44_app_vec3(shdr.out_ray_ws.dir, ctrl->cam.c_to_w, shdr.out_ray_ws.dir);
			vec3_eucl_nrmlz(shdr.out_ray_ws.dir, shdr.out_ray_ws.dir);
			reslum = trace_ray_to_scene(ctrl, shdr);
//t_color color = color_app_lum(reslum);

//printf("reslum %10f, %10f, %10f | color %#06x\n", reslum.val.r, reslum.val.g, reslum.val.b, color);
			((t_u32*)ctrl->img_data)[i * REN_W + j] = color_app_lum(reslum);
		}
printf("%.2f / 100.00\n", 100. * (i + 1.) / REN_H);
	}
}
