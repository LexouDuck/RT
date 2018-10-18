/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:23:19 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/01 10:17:14 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Calculates the euclidian quadratic distance from the head of our vector to
**	the y axis.
*/

static inline t_float		vec3_ynull_dot(t_vec_3d const v1, t_vec_3d const v2)
{
	return (v1[0] * v2[0] + v1[2] * v2[2]);
}

/*
** The infcylinder primitive is the set of points made by the circle of radius
** 1. translated by every vector (0., a, 0.) where a is a real number parameter.
**
** Any point on this primitive verifies x^2 + z^2 == 1.; thus one must find
**	r = o + td
**	(o+td)_x^2 + (o+td)_z^2 - 1.			== 0		<=>
**
**	(ox + t dx)^2 + (oz + t dz)^2 - 1.		== 0		<=>
**
**	(ox^2 + oz^2 - 1.)				+					<=>
**	2 * (oxdx + ozdz)	* t			+
**	(dx^2 + dz^2)		* t^2				== 0
*/

t_bool						intersect_ray_infcylinder(t_ray *objray)
{
	t_vec_3d	quadpoly;
	t_float		root1;
	t_float		root2;

	quadpoly[0] = vec3_ynull_dot(objray->dir, objray->dir);
	quadpoly[1] = 2 * vec3_ynull_dot(objray->dir, objray->pos);
	quadpoly[2] = vec3_ynull_dot(objray->pos, objray->pos) - 1.;
	if (!(get_realroots_quadpoly(&root1, &root2, quadpoly)))
		return (FALSE);
	if (root1 <= 0. || root2 <= 0. || (root1 > objray->t && root2 > objray->t))
		return (FALSE);
	objray->t = ft_fmin(root1, root2);
	return (TRUE);
}

/*
** This function should return TRUE iff objray.t has been updated; ie, iff
**	there is an intersection, and ray.origin is not located within the cylinder.
**
** Rays should arrive already converted to object space coordinates.
**
** The cylinder primitive is centered in (0., 0., 0.) by default, with 1. as
**	default radius, and (0., 1., 0.) as default height. This means the base
**	circle verifies {p = (x, -0.5, z) | x^2 + z^2 <= 1} and the top circle
**	{p = (x, +0.5, z) | x^2 + z^2 <= 1}
*/

t_bool						intersect_ray_cylinder(t_ray *objray)
{
	t_ray		tmp_ray;
	t_float		tmp;
	t_bool		is_in_hrz_area;
	t_bool		is_in_vrt_area;

	if ((is_in_hrz_area = (-0.5 <= objray->pos[1] && objray->pos[1] <= 0.5)) &&
		(is_in_vrt_area = (vec3_ynull_dot(objray->pos, objray->pos) <= 1.)))
		return (FALSE);
	tmp = 1. / 0.;
	tmp_ray = *objray;
	if (intersect_ray_infcylinder(&tmp_ray))
	{
		if (ft_fabs(tmp_ray.pos[1] + tmp_ray.t * tmp_ray.dir[1]) < 0.5)
			tmp = tmp_ray.t;
	}
	tmp_ray.t = objray->t;
	tmp_ray.pos[1] -= 0.5;
	if (!is_in_hrz_area && intersect_ray_disk(&tmp_ray))
		tmp = ft_fmin(tmp, tmp_ray.t);
	tmp_ray.t = objray->t;
	tmp_ray.pos[1] += 1.;
	if (!is_in_hrz_area && intersect_ray_disk(&tmp_ray))
		tmp = ft_fmin(tmp, tmp_ray.t);
	objray->t = ft_fmin(tmp, objray->t);
	return (objray->t == tmp);
}

/*
** Rays should arrive already converted to object space.
**
** Returns both vectors in object space. Note that on the unit infcylinder of
**	R3, every point on the cylinder corresponds to its unit normal, if one sets
**	the y coordinate to 0; as for every point on the cylinder x^2 + z^2 == 1
*/

void						get_hnn_infcylinder(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	vec3_set(normal, hitpos[0], 0., hitpos[2]);
}

void						get_hnn_cylinder(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	if (ft_fabs(hitpos[1] - 0.5) < APPROX)
		vec3_set(normal, 0., 1., 0.);
	else if (ft_fabs(hitpos[1] + 0.5) < APPROX)
		vec3_set(normal, 0., -1., 0.);
	else
		vec3_set(normal, hitpos[0], 0., hitpos[2]);
}
