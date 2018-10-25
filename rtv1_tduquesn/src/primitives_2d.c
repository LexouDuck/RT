/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 20:00:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/09/27 20:02:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** The primitive is the xz-plane.
**
** The first 'if' is true iff if they are of same sign (looking away from the
**	plane) or the ray is on the plane (pos_y = 0) or the ray is parallel to the
**	plane (dir_y = 0).
*/

t_bool		intersect_ray_plane(t_ray *objray)
{
	t_float		tmp;

	if (objray->pos[1] * objray->dir[1] >= 0.)
		return (FALSE);
	if ((tmp = -objray->pos[1] / objray->dir[1]) >= objray->t)
		return (FALSE);
	objray->t = tmp;
	return (TRUE);
}

/*
** The disk primitive is built to be horizontal (ie, parallel to the
**	xz-plane), and have radius 1.
*/

t_bool		intersect_ray_disk(t_ray *objray)
{
	t_ray		tmp_ray;
	t_float		tmp_x;
	t_float		tmp_z;

	tmp_ray = *objray;
	if (intersect_ray_plane(&tmp_ray))
	{
		tmp_x = tmp_ray.pos[0] + tmp_ray.t * tmp_ray.dir[0];
		tmp_z = tmp_ray.pos[2] + tmp_ray.t * tmp_ray.dir[2];
		if (tmp_x * tmp_x + tmp_z * tmp_z <= 1.)
		{
			objray->t = tmp_ray.t;
			return (TRUE);
		}
	}
	return (FALSE);
}

/*
** The square primitive is [-0.5, 0.5]_x × [-0.5, 0.5]_z
*/

t_bool		intersect_ray_square(t_ray *objray)
{
	t_ray		tmp_ray;
	t_float		tmp_x;
	t_float		tmp_z;

	tmp_ray = *objray;
	if (intersect_ray_plane(&tmp_ray))
	{
		tmp_x = tmp_ray.pos[0] + tmp_ray.t * tmp_ray.dir[0];
		tmp_z = tmp_ray.pos[2] + tmp_ray.t * tmp_ray.dir[2];
		if (-0.5 <= tmp_x && tmp_x <= 0.5 &&
			-0.5 <= tmp_z && tmp_z <= 0.5)
		{
			objray->t = tmp_ray.t;
			return (TRUE);
		}
	}
	return (FALSE);
}

/*
** The triangle primitive is {[-0.5]_x ; [0.5]_x ; [1.0]_z}
*/

t_bool		intersect_ray_triangle(t_ray *objray)
{
	t_ray		tmp_ray;
	t_float		tmp_x;
	t_float		tmp_z;
	t_float		tmp_zby2;

	tmp_ray = *objray;
	if (intersect_ray_plane(&tmp_ray))
	{
		tmp_x = tmp_ray.pos[0] + tmp_ray.t * tmp_ray.dir[0];
		tmp_z = tmp_ray.pos[2] + tmp_ray.t * tmp_ray.dir[2];
		tmp_zby2 = tmp_z / 2.;
		if (0. <= tmp_z && tmp_z <= 1. &&
			-tmp_zby2 <= tmp_x && tmp_x <= tmp_zby2)
		{
			objray->t = tmp_ray.t;
			return (TRUE);
		}
	}
	return (FALSE);
}

/*
** Works for all 2D primitives
*/

void		get_hnn_plane(t_vec_3d hitpos, t_vec_3d normal,
							t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	vec3_cpy(normal, (t_vec_3d){0., objray.pos[1] > 0 ? 1. : -1, 0.});
}
