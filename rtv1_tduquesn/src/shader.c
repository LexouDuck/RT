/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 07:05:34 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/09 14:47:20 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				vec3_schur(t_vec_3d res,
								t_vec_3d const v1, t_vec_3d const v2)
{
	res[0] = v1[0] * v2[0];
	res[1] = v1[1] * v2[1];
	res[2] = v1[2] * v2[2];
}

void				vec3_displace(t_vec_3d edit, t_float const coef,
									t_vec_3d const dir)
{
	t_vec_3d	scaled_dir;

	vec3_scale(scaled_dir, coef, dir);
	vec3_add(edit, edit, scaled_dir);
}

t_color				color_app_lum(t_vcolor const lum)
{
	t_u8		red;
	t_u8		grn;
	t_u8		blu;

	red = ft_fmax(0., ft_fmin(255., lum.val.r));
	grn = ft_fmax(0., ft_fmin(255., lum.val.g));
	blu = ft_fmax(0., ft_fmin(255., lum.val.b));
	return (red << 16 | grn << 8 | blu);
}

t_vcolor			get_lum_from_lightsrc(t_control *ctrl,
								t_shader const lgtshdr/*, t_float *costheta*/)
{
	t_vcolor	reslum;
	t_float		quaddist;
	t_float		costh;

	reslum.val = (t_rgb){0., 0., 0.};
	if (trace_ray_to_objs(ctrl, lgtshdr.in_ray, NULL, NULL))
		return (reslum);
	else
	{
		if (ctrl->show_diffuse)
		{
			quaddist = lgtshdr.in_ray.t * lgtshdr.in_ray.t;
			costh = vec3_dot(lgtshdr.normal, lgtshdr.in_ray.dir);
			vec3_scale(reslum.vec,
				INV_PI * lgtshdr.hit_obj->intensity * ft_fmax(0., costh) / quaddist,
				lgtshdr.hit_obj->rgb.vec);
		}
/*		if (ctrl->show_specular)
		{
			vec3_scale(ref, -1., lgtshdr.in_ray.dir);
			get_reflect(ref, ref, shdr.normal);
			tmp = ft_fmax(0., -vec3_dot(ref, shdr.objray_dir));
			vec3_set(spec, powf(tmp, shdr.obj_specul[0]),
				powf(tmp, shdr.obj_specul[1]), powf(tmp, shdr.obj_specul[2]));
			vec3_schur(spec, spec, lgtshdr.hit_obj.rgb);
		}
*/	}
	return (reslum);
}

#if 0
t_vcolor			get_lum_from_object(t_control *ctrl,
									t_shader shdr)
{
	t_shader	lgtshdr;
	t_vcolor	reslum;
	t_ray		ray;
	t_u32		i;
	t_u32		j;

	get_hitpos(ray.pos, shdr.in_ray);
	vec3_displace(ray.pos, APPROX, shdr.normal);
	i = 0;
	while (i < ctrl->spotlst_len)
	{
		j = 0;
		while (j < RAY_SAMPLE_NB)
		{
			ray.dir
			++j;
		}
		lgtshdr.
		++i;
	}
	reslum = get_lum_from_lightsrc(ctrl, lgtshdr);
	vec3_schur(reslum.vec, reslum.vec, shdr.hit_obj->rgb);
	return (reslum);
}


t_vcolor			get_spec_from_object(t_control *ctrl,
										t_shader shdr, t_shader lgtshdr)
{
	t_vcolor	reslum;
	t_float		quaddist;

	if (trace_ray_to_objs(ctrl, shdr.in_ray, NULL, NULL))
	{
		reslum.vec = (t_vec_3d){0., 0., 0.};
	}
	else
	{
		vec3_scale(ref, -1., shdr.in_ray.dir);
		get_reflect(ref, ref, shdr.normal);
		tmp = ft_fmax(0., -vec3_dot(ref, shdr.objray_dir));
		vec3_set(spec, powf(tmp, shdr.obj_specul[0]),
			powf(tmp, shdr.obj_specul[1]), powf(tmp, shdr.obj_specul[2]));
		vec3_schur(spec, spec, spot.rgb);
	}
	return (reslum);
}

static void			shader_get_diff_n_spec(t_control *ctrl,
										t_shader shdr)//, t_light const spot)
{
	t_vec_3d	reslum;
	t_float		tmp;
	t_vec_3d	ref;
	t_vec_3d	spec;

//	vec3_sub(shdr.dirlight.dir, spot.pos, shdr.dirlight.pos);
//	tmp = vec3_eucl_quadnorm(shdr.dirlight.dir);
//	shdr.dirlight.t = sqrt(tmp);
	vec3_scale(shdr.dirlight.dir, 1. / shdr.dirlight.t, shdr.dirlight.dir);

	if (ctrl->show_diffuse)
	{
		if (shdr.hit_obj.material != lightsrc && 
			trace_ray_to_objs(ctrl, shdr.dirlight, NULL, NULL))
			return ;
		vec3_scale(reslum, INV_PI * spot.intensity * ft_fmax(0.,
			vec3_dot(shdr.normal, shdr.dirlight.dir)) / tmp, shdr.obj_albedo);
		vec3_schur(reslum, reslum, spot.rgb);
	}

	if (ctrl->show_specular)
	{
		vec3_scale(ref, -1., shdr.dirlight.dir);
		get_reflect(ref, ref, shdr.normal);
		tmp = ft_fmax(0., -vec3_dot(ref, shdr.objray_dir));
		vec3_set(spec, powf(tmp, shdr.obj_specul[0]),
			powf(tmp, shdr.obj_specul[1]), powf(tmp, shdr.obj_specul[2]));
		vec3_schur(spec, spec, spot.rgb);
	}
	//vec3_add(reslum, reslum, spec);
}


void					get_lighting_at_point(t_control *ctrl,
							t_object const obj, t_ray const objray, int is_direct)
{
	t_shader		shdr;
	t_ray_sample	raysamp;

	//for each vector in  sample
		//get intersection point on primitive (dirlight.pos) and "normal fix" it
		//get normal at point of intersection
		//set ray origin to world space
		//

	//loop on spotlst
	//loop on objlst
}
#endif


/*
** Principle: you cast a ray from the point of contact in question to the light
** source(s) and if it intersects with an object, and
** 		dist(contact, light) > dist(contact, shadow_ray_contact)
** then the contact point is hidden from the light source
*/
/*
t_vcolor				get_color_from_fixed_objray(t_control *ctrl,
							t_object const obj, t_ray const objray)
{
	t_shader	shdr;
	t_vcolor	lum;
	t_vec_3d	tmp;
//	t_light		cur_spot;
	int			i;

	
	obj.get_hnn(shdr.dirlight.pos, shdr.normal, objray);



	vec3_scale(tmp, APPROX, shdr.normal);
	vec3_add(shdr.dirlight.pos, shdr.dirlight.pos, tmp);
	mat44_app_vec3(shdr.dirlight.pos, obj.o_to_w, shdr.dirlight.pos);
	mat33_mul(shdr.normal, obj.n_to_w, shdr.normal);
	vec3_eucl_nrmlz(shdr.normal, shdr.normal);
	vec3_cpy(shdr.obj_albedo, obj.albedo);
	vec3_cpy(shdr.obj_specul, obj.specul);
	mat33_app_vec(shdr.objray_dir, obj.linear_o_to_w, objray.dir);
	vec3_set(lum, 0., 0., 0.);
	i = -1;
	while (++i < ctrl->spotlst_len)
	{
		cur_spot = ctrl->spotlst[i];
		shader_get_directlgt(ctrl, 
		shader_get_diff_n_spec(ctrl, shdr, cur_spot);
	}
	return (lum);
}
*/
