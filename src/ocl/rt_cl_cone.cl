/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt._cl_cone.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_intersection		rt_cl_infcone_hole_view_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3 		quadpoly;
	float2		roots;
	bool		ray_hrz_orient;

	quadpoly.x = rt_cl_float3_yneg_dot(ray.dir, ray.dir);
	quadpoly.y = 2.f * rt_cl_float3_yneg_dot(ray.dir, ray.pos);
	quadpoly.z = rt_cl_float3_yneg_dot(ray.pos, ray.pos);
	if(!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (INTER_NONE);
	ray_hrz_orient = (ray.dir.y * roots.x + ray.pos.y) *
					(ray.dir.y * roots.y + ray.pos.y) >= 0.f;
	if (roots.x <= 0.f)
	{
		*res = roots.y;
		return (ray_hrz_orient ? INTER_INSIDE : INTER_OUTSIDE);
	}
	else if (roots.y <= 0.f)
	{
		*res = roots.x;
		return (ray_hrz_orient ? INTER_INSIDE : INTER_OUTSIDE);
	}
	*res = (ray_hrz_orient) ? fmin(roots.x, roots.y) :
							  fmax(roots.x, roots.y) ;
	return (ray_hrz_orient ? INTER_OUTSIDE : INTER_INSIDE);
}

/*
** The cone primitive is an infcone from 0. to 1. on the y axis, and a circle
** of radius one, in the affine plane "xz + (0, 1, 0)" and centered in (0,1,0).
**
** This means the position of the cone in world space should coincide with
** the point of the cone.
*/

static t_intersection		rt_cl_cone_intersect
(
							float *		res,
							t_ray		ray
)
{
	t_ray			tmp_ray;
	float			hy;
	float			tmp;
	bool			is_in_infcone;
	bool			is_in_hrz_area;
	t_intersection	inter;

	is_in_infcone = (rt_cl_float3_yneg_dot(ray.pos, ray.pos) <= 0.f);
	is_in_hrz_area = (0.f <= ray.pos.y && ray.pos.y <= 1.f);
	tmp = 1.f / 0.f;
	tmp_ray = ray;
	tmp_ray.t = tmp;
	tmp_ray.inter_type = rt_cl_infcone_hole_view_intersect(&(tmp_ray.t), tmp_ray);
	if (tmp_ray.inter_type)
	{
		hy = tmp_ray.pos.y + tmp_ray.dir.y * tmp_ray.t;
		tmp = (0.f < hy && hy < 1.f) ? tmp_ray.t : tmp;
	}
	tmp_ray.t = 1.f / 0.f;
	tmp_ray.pos.y -= 1.f;
	tmp_ray.inter_type = rt_cl_disk_intersect(&(tmp_ray.t), tmp_ray);
	if (tmp_ray.inter_type)
	{
		tmp = fmin(tmp, tmp_ray.t);
	}
	*res = fmin(tmp, ray.t);
	inter = *res == tmp ? INTER_OUTSIDE : INTER_NONE;
	inter = is_in_hrz_area && is_in_infcone ? INTER_INSIDE : inter;
	return (inter);
}

/*
** Notice that if one reflects hitpos over the xz-plane, one obtains a scaled
**	version of the normal at hitpos.
*/

static float3		rt_cl_cone_get_normal
(
							float3		hitpos
)
{
	float3 	normal;

	if (fabs(hitpos.y - 1.f) < EPS)
	{
		normal = (float3)(0.f, 1.f, 0.f);
	}
	else
	{
		normal = (float3)(hitpos.x, -hitpos.y, hitpos.z);	
		normal = normalize(normal);
	}
	return (normal);
}