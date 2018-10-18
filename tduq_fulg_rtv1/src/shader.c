/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 07:05:34 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/18 18:04:58 by fulguritu        ###   ########.fr       */
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

static t_color		color_app_lum(t_vec_3d lum)
{
	t_u8		red;
	t_u8		grn;
	t_u8		blu;

	red = ft_fmax(0., ft_fmin(255., lum[0]));
	grn = ft_fmax(0., ft_fmin(255., lum[1]));
	blu = ft_fmax(0., ft_fmin(255., lum[2]));
	return (red << 16 | grn << 8 | blu);
}

/*
** Returns the result of light and object albedo color construction
**
**	"vec3_scale(shdr.dirlight.dir, 1. / shdr.dirlight.t, shdr.dirlight.dir);"
**		is
**	"vec3_eucl_nrmlz(shdr.dirlight.dir, shdr.dirlight.dir);"
**		but less costly in this context.
**
**	//	vec3_set(reslum, 0., 0., 0.); should be added unless set in previous
**			function.
*/

static void			shader_get_diff_n_spec(t_vec_3d reslum, t_control *ctrl,
										t_shader shdr, t_light const spot)
{
	t_float		tmp;
	t_vec_3d	ref;
	t_vec_3d	spec;

	vec3_sub(shdr.dirlight.dir, spot.pos, shdr.dirlight.pos);
	tmp = vec3_eucl_quadnorm(shdr.dirlight.dir);
	shdr.dirlight.t = sqrt(tmp);
	vec3_scale(shdr.dirlight.dir, 1. / shdr.dirlight.t, shdr.dirlight.dir);
	if (trace_ray_to_objs(ctrl, shdr.dirlight, NULL, NULL))
		return ;
	if (ctrl->show_diffuse)
	{
		vec3_scale(reslum, INV_PI * spot.intensity * ft_fmax(0.,
			vec3_dot(shdr.normal, shdr.dirlight.dir)) / tmp, shdr.obj_albedo);
		vec3_schur(reslum, reslum, spot.rgb);
	}
	if (!(ctrl->show_specular))
		return ;
	vec3_scale(ref, -1., shdr.dirlight.dir);
	get_reflect(ref, ref, shdr.normal);
	tmp = ft_fmax(0., -vec3_dot(ref, shdr.objray_dir));
	vec3_set(spec, powf(tmp, shdr.obj_specul[0]),
		powf(tmp, shdr.obj_specul[1]), powf(tmp, shdr.obj_specul[2]));
	vec3_schur(spec, spec, spot.rgb);
	vec3_add(reslum, reslum, spec);
}

/*
** Principle: you cast a ray from the point of contact in question to the light
** source(s) and if it intersects with an object, and
** 		dist(contact, light) > dist(contact, shadow_ray_contact)
** then the contact point is hidden from the light source
*/

t_color				get_color_from_fixed_objray(t_control *ctrl,
							t_object const obj, t_ray const objray)
{
	t_shader	shdr;
	t_vec_3d	lum;
	t_vec_3d	tmp;
	t_light		cur_spot;
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
		vec3_set(tmp, 0., 0., 0.);
		cur_spot = ctrl->spotlst[i];
		shader_get_diff_n_spec(tmp, ctrl, shdr, cur_spot);
		vec3_add(lum, lum, tmp);
	}
	return (color_app_lum(lum));
}
