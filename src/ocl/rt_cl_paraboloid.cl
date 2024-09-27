/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_paraboloid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static t_intersection		rt_cl_paraboloid_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		quadpoly;
	float2		roots;

	quadpoly.x = rt_cl_float3_ynull_dot(ray.dir, ray.dir);
	quadpoly.y = 2.f * rt_cl_float3_ynull_dot(ray.dir, ray.pos) - ray.dir.y;
	quadpoly.z = rt_cl_float3_ynull_dot(ray.pos, ray.pos) - ray.pos.y;
	if (!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (INTER_NONE);
	else if (roots.x <= 0.f)
	{
		*res = roots.y;
		return (INTER_INSIDE);
	}
	else if (roots.y <= 0.f)
	{
		*res = roots.x;
		return (INTER_INSIDE);
	}
	else
	{
		*res = fmin(roots.x, roots.y);
		return (INTER_OUTSIDE);
	}
}

/*
** To find the normal of a parabola, consider the fact that a parabola is a
** manifold and can thus be described through its calculus form.
**
** Our scalar function for our hypersurface is f(x, y, z) = x^2 - y + z^2
** Its jacobian matrix is thus the 1×3 matrix [ 2x, -1, 2z ]
*/
static float3			rt_cl_paraboloid_get_normal
(
						float3 hitpos
)
{
	float3		normal;

	normal = (float3)(2.f * hitpos.x, -1.f, 2.f * hitpos.z);
	normal = normalize(normal);
	return (normal);
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
**
*/
static t_intersection			rt_cl_saddle_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		quadpoly;
	float2		roots;
	bool		is_inter_inside;

	quadpoly.x = ray.dir.x * ray.dir.x - ray.dir.z * ray.dir.z;
	quadpoly.y = 2.f * (ray.dir.x * ray.pos.x - ray.dir.z * ray.pos.z) - ray.dir.y;
	quadpoly.z = ray.pos.x * ray.pos.x - ray.pos.z * ray.pos.z - ray.pos.y;
	if (!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (INTER_NONE);
	is_inter_inside = quadpoly.z < 0.f;
	if (roots.x <= 0.f)
	{
		*res = roots.y;
		return (is_inter_inside ? INTER_INSIDE : INTER_OUTSIDE);
	}
	else if (roots.y <= 0.f)
	{
		*res = roots.x;
		return (is_inter_inside ? INTER_INSIDE : INTER_OUTSIDE);
	}
	*res = fmin(roots.x, roots.y);
	return (is_inter_inside ? INTER_INSIDE : INTER_OUTSIDE);
}

/*
** To find the normal of a parabola, consider the fact that a parabola is a
** manifold and can thus be described through its calculus form.
**
** Our scalar function for our hypersurface is f(x, y, z) = x^2 - y - z^2
** Its jacobian matrix is thus the 1×3 matrix [ 2x, -1, -2z ]
*/
static float3			rt_cl_saddle_get_normal
(
						float3 hitpos
)
{
	float3		normal;

	normal = (float3)(2.f * hitpos.x, -1.f, -2.f * hitpos.z);
	normal = normalize(normal);
	return (normal);
}
