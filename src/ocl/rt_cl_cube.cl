/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_cube.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static bool					rt_cl_point_is_in_bbox
(
					float3		pos,
					t_bbox		aabb
)
{
	return (aabb.vi.x < pos.x && pos.x < aabb.vf.x &&
			aabb.vi.y < pos.y && pos.y < aabb.vf.y &&
			aabb.vi.z < pos.z && pos.z < aabb.vf.z);
}

static t_intersection		rt_cl_ray_intersect_bbox
(
					t_ray		ray,
					t_bbox		aabb,
					float		tmin,
					float		tmax,
					float *		tres
)
{
	t_intersection	inter;
	float			tmax_old = tmax;
	//TODO add aabb.vi.x < ray.pos.x < aabb.vf.x: if true for every coordinate, return INTER_INSIDE

	float3	inv_dir = native_recip(ray.dir);
	//get all plane intersections
	float3	ti = (aabb.vi - ray.pos) * inv_dir;
	float3	tf = (aabb.vf - ray.pos) * inv_dir;

	//put all inferior bounds in tinf, and all superior bounds in tsup
	float3	tinf = fmin(ti, tf);
	float3	tsup = fmax(ti, tf);

	// get biggest inferorior bound tmin and smallest superior bound tmax.
	tmin = fmax(tmin, fmax(tinf.x, fmax(tinf.y, tinf.z)));
	tmax = fmin(tmax, fmin(tsup.x, fmin(tsup.y, tsup.z)));

	//intersection iff no incoherence in all previous checks and tmin = Max(inferior bound) < Min(superior bound) = tmax
	inter = tmin < tmax ? INTER_OUTSIDE : INTER_NONE;
	*tres = inter ? tmin : tmax_old;
	if (*tres < EPS)
	{
		*tres = tmax;
		inter = INTER_INSIDE;
	}
	return (inter);
}

static t_intersection		rt_cl_cube_intersect
(
							float *		res,
							t_ray		ray
)
{
	float			tmin = 0.;
	float			tmax = ray.t;
	t_bbox			aabb = (t_bbox){(float3)(-1., -1., -1.),
					(float3)(1., 1., 1.)};
	t_intersection	inter;

	inter = rt_cl_ray_intersect_bbox(ray, aabb, tmin, tmax, res);
	return (inter);
}

static float3				rt_cl_cube_get_normal
(
							float3 hitpos
)
{
	if (fabs((float)(hitpos.x - 1.)) <= EPS)
		return ((float3)(1., 0., 0.));
	else if (fabs((float)(hitpos.x + 1.)) <= EPS)
		return ((float3)(-1., 0., 0.));
	else if (fabs((float)(hitpos.y - 1.)) <= EPS)
		return ((float3)(0., 1., 0.));
	else if (fabs((float)(hitpos.y + 1.)) <= EPS)
		return ((float3)(0., -1., 0.));
	else if (fabs((float)(hitpos.z - 1.)) <= EPS)
		return ((float3)(0., 0., 1.));
	else if (fabs((float)(hitpos.z + 1.)) <= EPS)
		return ((float3)(0., 0., -1.));
	else
		return ((float3)(0., 0., 0.));
}
