/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:23:47 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/25 00:59:08 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Returns the point on the object hit by a ray in object space coordinates.
*/

inline void		get_ray_hitpos(t_vec_3d hitpos, t_ray const objray)
{
	vec3_scale(hitpos, objray.t, objray.dir);
	vec3_add(hitpos, hitpos, objray.pos);
}

/*
** Homogeneous model 4*4 matrix applied to 3*1 vector
*/
t_ray			ray_x_to_y(t_mat_4b4 const x_to_y,
						t_mat_3b3 const linear_x_to_y,
						t_ray const ray)
{
	t_ray		result;

	mat44_app_vec3(result.pos, x_to_y, ray.pos);
	mat33_app_vec(result.dir, linear_x_to_y, ray.dir);
//	vec3_eucl_nrmlz(result.dir, result.dir);
	result.t = ray.t;
	result.depth = ray.depth;
	result.sray_depth = ray.sray_depth;
	return (result);
}

inline void		get_reflect(t_vec_3d refdir,
							t_vec_3d const incdir,
							t_vec_3d const normal)
{
	vec3_scale(refdir, -2 * vec3_dot(incdir, normal), normal);
	vec3_add(refdir, refdir, incdir);
}

/*
** The normal and in_ray.dir should be set.
*/

inline void		shader_get_reflect(t_shader *shdr)
{
	get_reflect(shdr->out_ray_os.dir, shdr->in_ray.dir, shdr->normal_os);
/*	vec3_scale(,
		-2 * vec3_dot(shdr->in_ray.dir, shdr->normal_os), shdr->normal_os);
	vec3_add(shdr->out_ray_os.dir, shdr->out_ray_os.dir, shdr->in_ray.dir);
*/
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
