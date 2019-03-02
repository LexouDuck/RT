/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_primitives_2d.cl                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The primitive is the xz-plane.
**
** The first 'if' is true iff if they are of same sign (looking away from the
**	plane) or the ray is on the plane (pos_y = 0) or the ray is parallel to the
**	plane (dir_y = 0).
*/
static t_intersection		rt_cl_plane_intersect
(
							float *		res,
							t_ray		ray
)
{
	float		tmp;

	if (ray.pos.y * ray.dir.y >= 0.)
		return (INTER_NONE);
	if ((tmp = -ray.pos.y / ray.dir.y) >= ray.t)
		return (INTER_NONE);
	*res = tmp;
	return (ray.pos.y > 0. ? INTER_OUTSIDE : INTER_INSIDE);
}

/*
** The disk primitive is built to be horizontal (ie, parallel to the
**	xz-plane), and have radius 1.
*/
static t_intersection		rt_cl_disk_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		tmp;

	ray.inter_type = rt_cl_plane_intersect(res, ray);
	if (ray.inter_type)
	{
		ray.t = *res;
		tmp.x = ray.pos.x + ray.t * ray.dir.x;
		tmp.z = ray.pos.z + ray.t * ray.dir.z;
		if (tmp.x * tmp.x + tmp.z * tmp.z <= 1.)
		{
			*res = ray.t;
			return (ray.inter_type);
		}
	}
	return (INTER_NONE);
}

/*
** The square primitive is [-0.5, 0.5]_x × [-0.5, 0.5]_z
*/
static t_intersection		rt_cl_rectangle_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		tmp;

	ray.inter_type = rt_cl_plane_intersect(res, ray);
	if (ray.inter_type)
	{
		ray.t = *res;
		tmp.x = ray.pos.x + ray.t * ray.dir.x;
		tmp.z = ray.pos.z + ray.t * ray.dir.z;
		if (-0.5 <= tmp.x && tmp.x <= 0.5 &&
			-0.5 <= tmp.z && tmp.z <= 0.5)
		{
			*res = ray.t;
			return (ray.inter_type);
		}
	}
	return (INTER_NONE);
}

/*
** The triangle primitive is {[-0.5]_x ; [0.5]_x ; [1.0]_z}
*/
static t_intersection		rt_cl_triangle_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		tmp;
	float		tmp_zby2;

	ray.inter_type = rt_cl_plane_intersect(res, ray);
	if (ray.inter_type)
	{
		ray.t = *res;
		tmp.x = ray.pos.x + ray.t * ray.dir.x;
		tmp.z = ray.pos.z + ray.t * ray.dir.z;
		tmp_zby2 = tmp.z / 2.;
		if (0. <= tmp.z && tmp.z <= 1. &&
			-tmp_zby2 <= tmp.x && tmp.x <= tmp_zby2)
		{
			*res = ray.t;
			return (ray.inter_type);
		}
	}
	return (INTER_NONE);
}

/*
** Works for all 2D primitives
*/
static float3				rt_cl_plane_get_normal
(
							float3 hitpos
)
{
//	hitpos = get_ray_hitpos(hitpos, ray);
	return ((float3)(0., 1., 0.));
}
