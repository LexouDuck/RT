/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void	intersect_cube_axis(
	float *tmin,
	float *tmax,
	float orig,
	float dir)
{
	float	invdir;
	float	coord;

	invdir = (1 / dir);
	coord = (invdir < 0) ? -1 : 1;
	*tmin = (coord - orig) * invdir;
	*tmax = (-coord - orig) * invdir;
	if (*tmin > *tmax)
	{
		coord = *tmin;
		*tmin = *tmax;
		*tmax = coord;
	}
}

int			intersect_cube(t_object *object, t_ray *ray)
{
	t_vector	min;
	t_vector	max;

	if (!object)
		return (0);
	intersect_cube_axis(&min.x, &max.x, ray->pos.x, ray->dir.x);
	intersect_cube_axis(&min.y, &max.y, ray->pos.y, ray->dir.y);
	if ((min.x > max.y) || (min.y > max.x))
		return (0);
	if (min.y > min.x)
		min.x = min.y;
	if (max.y < max.x)
		max.x = max.y;
	intersect_cube_axis(&min.z, &max.z, ray->pos.z, ray->dir.z);
	if ((min.x > max.z) || (min.z > max.x))
		return (0);
	if (min.z > min.x)
		min.x = min.z;
	if (max.z < max.x)
		max.x = max.z;
	ray->t = (min.x < max.x) ? min.x : max.x;
	return (ray->t >= 0);
}

void		getnormal_cube(
	t_vector *result,
	t_object *object,
	t_vector *hit_pos)
{
	t_vector	tmp;

	if (!object)
		return ;
	vector_set(&tmp,
		(hit_pos->x < 0 ? -hit_pos->x : hit_pos->x),
		(hit_pos->y < 0 ? -hit_pos->y : hit_pos->y),
		(hit_pos->z < 0 ? -hit_pos->z : hit_pos->z));
	if (tmp.x == tmp.y && tmp.y == tmp.z)
	{
		vector_set(result, hit_pos->x, hit_pos->y, hit_pos->z);
		vector_normalize(result);
	}
	else if (tmp.x >= tmp.y && tmp.x >= tmp.z)
		vector_set(result, (hit_pos->x < 0 ? -1 : 1), 0, 0);
	else if (tmp.y >= tmp.x && tmp.y >= tmp.z)
		vector_set(result, 0, (hit_pos->y < 0 ? -1 : 1), 0);
	else if (tmp.z >= tmp.x && tmp.z >= tmp.y)
		vector_set(result, 0, 0, (hit_pos->z < 0 ? -1 : 1));
}
