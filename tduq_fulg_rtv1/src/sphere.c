/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 22:59:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/09/16 23:00:18 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** This function should return TRUE iff objray.t has been updated.
** Rays should arrive already converted to object space coordinates.
**
** The sphere primitive is centered in (0., 0., 0.) by default.
** Since 1. is the default radius, 1. * 1. = 1. is the quadratic norm of our
**		sphere primitive.
**
** Any point on this primitive verifies x^2 + y^2 + z^2 == 1; thus one must find
**	r = o + td
**	(o+td)_x^2 + (o+td)_z^2 + (o+td)_y^2 - 1.			== 0		<=>
**
**	(ox + t dx)^2 + (oz + t dz)^2 + (oy + t dy)^2 - 1.	== 0		<=>
**
**	(ox^2 + oz^2 + oy^2) - 1.			+							<=>
**	2 * (oxdx + ozdz + oydy)	* t		+
**	(dx^2 + dz^2 + dy^2)		* t^2					== 0
*/

t_bool		intersect_ray_sphere(t_ray *objray)
{
	t_vec_3d	quadpoly;
	t_float		root1;
	t_float		root2;

	quadpoly[0] = vec3_eucl_quadnorm(objray->dir);
	quadpoly[1] = 2 * vec3_dot(objray->dir, objray->pos);
	quadpoly[2] = vec3_eucl_quadnorm(objray->pos) - 1.;
	if (!(get_realroots_quadpoly(&root1, &root2, quadpoly)))
		return (FALSE);
	if (root1 <= 0. || root2 <= 0. || (root1 > objray->t && root2 > objray->t))
		return (FALSE);
	objray->t = ft_fmin(root1, root2);
	return (TRUE);
}

/*
** Rays should arrive already converted to object space.
**
** Returns both vectors in object space. Note that on the unit sphere of R3,
** every point on the sphere corresponds to its unit normal.
*/

void		get_hnn_sphere(t_vec_3d hitpos, t_vec_3d normal,
									t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	vec3_cpy(normal, hitpos);
}
