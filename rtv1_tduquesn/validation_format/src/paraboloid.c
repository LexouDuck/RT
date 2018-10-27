/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:16:45 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 12:55:53 by fulguritu        ###   ########.fr       */
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
** The paraboloid primitive is the set of points made by the rotation of the
**	curve x^2 = y around the y-axis.
**
** Any point on this primitive verifies x^2 + z^2 == y; thus one must find
**	r = o + td
**	(o+td)_x^2 + (o+td)_z^2 - (o+td)_y			== 0		<=>
**
**	(ox + t dx)^2 + (oz + t dz)^2 - (oy + t dy)	== 0		<=>
**
**	(ox^2 + oz^2 - oy)						+				<=>
**	(2 * (oxdx + ozdz) - dy)	* t			+
**	(dx^2 + dz^2)				* t^2			== 0
*/

t_bool						intersect_ray_paraboloid(t_ray *objray)
{
	t_vec_3d	quadpoly;
	t_float		root1;
	t_float		root2;

	quadpoly[0] = vec3_ynull_dot(objray->dir, objray->dir);
	quadpoly[1] = 2 * vec3_ynull_dot(objray->dir, objray->pos) - objray->dir[1];
	quadpoly[2] = vec3_ynull_dot(objray->pos, objray->pos) - objray->pos[1];
	if (!(get_realroots_quadpoly(&root1, &root2, quadpoly)))
		return (FALSE);
	if (root1 <= 0. || root2 <= 0. || (root1 > objray->t && root2 > objray->t))
		return (FALSE);
	objray->t = ft_fmin(root1, root2);
	return (TRUE);
}

/*
** To find the normal of a parabola, consider the fact that a parabola is a
** manifold and can thus be described as though its calculus form.
**
** Our scalar function for our hypersurface is f(x, y, z) = x^2 - y + z^2
** Its jacobian matrix is thus the 1×3 matrix [ 2x, -1, 2z ]
*/

void						get_hnn_paraboloid(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	vec3_set(normal, 2 * hitpos[0], -1., 2 * hitpos[2]);
	vec3_eucl_nrmlz(normal, normal);
}

/*
** The paraboloid primitive is the set of points made by the rotation of the
**	curve x^2 = y around the y-axis.
**
** Any point on this primitive verifies x^2 - z^2 == y; thus one must find
**	r = o + td
**	(o+td)_x^2 - (o+td)_z^2 - (o+td)_y			== 0		<=>
**
**	(ox + t dx)^2 - (oz + t dz)^2 - (oy + t dy)	== 0		<=>
**
**	(ox^2 - oz^2 - oy)						+				<=>
**	(2 * (oxdx - ozdz) - dy)	* t			+
**	(dx^2 - dz^2)				* t^2			== 0
*/

t_bool						intersect_ray_saddle(t_ray *objray)
{
	t_vec_3d	quadpoly;
	t_float		root1;
	t_float		root2;

	quadpoly[0] = objray->dir[0] * objray->dir[0]
					- objray->dir[2] * objray->dir[2];
	quadpoly[1] = 2 * (objray->dir[0] * objray->pos[0]
					- objray->dir[2] * objray->pos[2]) - objray->dir[1];
	quadpoly[2] = objray->pos[0] * objray->pos[0]
					- objray->pos[2] * objray->pos[2] - objray->pos[1];
	if (!(get_realroots_quadpoly(&root1, &root2, quadpoly)))
		return (FALSE);
	if (root1 <= 0. && root2 <= 0.)
		return (FALSE);
	if (root1 <= 0.)
		root1 = root2;
	else if (root2 <= 0.)
		root2 = root1;
	if (root1 > objray->t && root2 > objray->t)
		return (FALSE);
	objray->t = ft_fmin(root1, root2);
	return (TRUE);
}

/*
** To find the normal of a parabola, consider the fact that a parabola is a
** manifold and can thus be described as though its calculus form.
**
** Our scalar function for our hypersurface is f(x, y, z) = x^2 - y - z^2
** Its jacobian matrix is thus the 1×3 matrix [ 2x, -1, -2z ]
*/

void						get_hnn_saddle(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	vec3_set(normal, 2. * hitpos[0], -1., -2. * hitpos[2]);
	if (objray.pos[0] * objray.pos[0] - objray.pos[2] * objray.pos[2]
				<= objray.pos[1])
		vec3_scale(normal, -1., normal);
	vec3_eucl_nrmlz(normal, normal);
}
