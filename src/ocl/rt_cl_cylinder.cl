/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_cylinder.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_intersection		rt_cl_infcylinder_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		quadpoly;
	float2		roots;

	quadpoly.x = rt_cl_float3_ynull_dot(ray.dir, ray.dir);
	quadpoly.y = 2.f * rt_cl_float3_ynull_dot(ray.dir, ray.pos);
	quadpoly.z = rt_cl_float3_ynull_dot(ray.pos, ray.pos) - 1.f;
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

static float3				rt_cl_infcylinder_get_normal
(
							float3 hitpos
)
{
	return ((float3)(hitpos.x, 0.f, hitpos.z));
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


static t_intersection		rt_cl_cylinder_intersect
(
							float *		res,
							t_ray		ray
)
{
	t_ray			tmp_ray;
	float			tmp;
	bool			is_in_hrz_area;
	bool			is_in_vrt_area;
	t_intersection	inter;

	is_in_hrz_area = (-1.f <= ray.pos.y && ray.pos.y <= 1.f);
	is_in_vrt_area = (rt_cl_float3_ynull_dot(ray.pos, ray.pos) <= 1.f);
	tmp = 1.f / 0.f;
	tmp_ray = ray;
	tmp_ray.inter_type = rt_cl_infcylinder_intersect(res, tmp_ray);
	if (tmp_ray.inter_type)
	{
		tmp_ray.t = *res;
		if (fabs((float)(tmp_ray.pos.y + tmp_ray.t * tmp_ray.dir.y)) < 1.f)
		{
			tmp = tmp_ray.t;
		}
	}
	tmp_ray.t = ray.t;
	tmp_ray.pos.y -= 1.f;
	tmp_ray.inter_type = rt_cl_disk_intersect(res, tmp_ray);
	if (tmp_ray.inter_type)
	{
		tmp_ray.t = *res;
		tmp = fmin(tmp, tmp_ray.t);
	}
	tmp_ray.t = ray.t;
	tmp_ray.pos.y += 2.f;
	tmp_ray.inter_type = rt_cl_disk_intersect(res, tmp_ray);
	if (tmp_ray.inter_type)
	{
		tmp_ray.t = *res;
		tmp = fmin(tmp, tmp_ray.t);
	}
	ray.t = fmin(tmp, ray.t);
	*res = ray.t;
	inter = ray.t == tmp ? INTER_OUTSIDE : INTER_NONE;
	inter = inter && is_in_hrz_area && is_in_vrt_area ? INTER_INSIDE : inter;
	return (inter);
}


/*
** Rays should arrive already converted to object space.
**
** Returns both vectors in object space. Note that on the unit infcylinder of
**	R3, every point on the cylinder corresponds to its unit normal, if one sets
**	the y coordinate to 0; as for every point on the cylinder x^2 + z^2 == 1
*/


static float3				rt_cl_cylinder_get_normal
(
							float3		hitpos
)
{
	if (fabs((float)(hitpos.y - 1.f)) < EPS)
		return ((float3)(0.f, 1.f, 0.f));
	else if (fabs((float)(hitpos.y + 1.f)) < EPS)
		return ((float3)(0.f, -1.f, 0.f));
	else
		return ((float3)(hitpos.x, 0.f, hitpos.z));
}