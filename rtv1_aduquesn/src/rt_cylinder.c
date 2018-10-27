/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int			intersect_disk(t_ray *ray, float altitude, float *t)
{
	t_vector	v;
	float		tmp;
	float		distance;

	tmp = -(altitude * altitude);
	if (altitude * ray->dir.y == 0)
		return (0);
	distance = -(altitude * ray->pos.y + tmp);
	distance /= (altitude * ray->dir.y);
	if (distance < 0)
		return (0);
	v.x = ray->pos.x + distance * ray->dir.x;
	v.y = ray->pos.y + distance * ray->dir.y;
	v.z = ray->pos.z + distance * ray->dir.z;
	if (v.x * v.x + v.z * v.z - 1 > 0)
		return (0);
	*t = distance;
	return (1);
}

int			intersect_infinite_cylinder(t_ray *ray)
{
	t_vector	v;
	float		root1;
	float		root2;
	float		delta;
	float		tmp;

	v.x = (ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z);
	v.y = (ray->dir.x * ray->pos.x + ray->dir.z * ray->pos.z) * 2;
	v.z = (ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z) - 1;
	delta = v.y * v.y - 4 * v.x * v.z;
	if (delta < 0)
		return (0);
	tmp = 0.5 / v.x;
	delta = sqrt(delta);
	root1 = (-v.y + delta) * tmp;
	root2 = (-v.y - delta) * tmp;
	if (root1 <= 0 || root2 <= 0 || (root1 > ray->t && root2 > ray->t))
		return (0);
	ray->t = (root1 < root2) ? root1 : root2;
	return (1);
}

int			intersect_cylinder(t_object *object, t_ray *ray)
{
	t_ray		tmp;
	float		t;
	int			inside_h;
	int			inside_v;

	if (!object || (
	(inside_h = (-1 <= ray->pos.y && ray->pos.y <= 1)) &&
	(inside_v = ((ray->pos.x * ray->pos.x + ray->pos.z * ray->pos.z) <= 1))))
		return (0);
	t = 1. / 0.;
	tmp = *ray;
	if (intersect_infinite_cylinder(&tmp))
	{
		if (fabsf(tmp.pos.y + tmp.t * tmp.dir.y) < 1)
			t = tmp.t;
	}
	tmp.t = ray->t;
	if (!inside_h && intersect_disk(&tmp, 1, &tmp.t))
		t = (t < tmp.t) ? t : tmp.t;
	tmp.t = ray->t;
	if (!inside_h && intersect_disk(&tmp, -1, &tmp.t))
		t = (t < tmp.t) ? t : tmp.t;
	ray->t = (t < ray->t) ? t : ray->t;
	return (ray->t == t);
}

void		getnormal_cylinder(
	t_vector *result,
	t_object *object,
	t_vector *hit_pos)
{
	if (!object)
		return ;
	else if (hit_pos->y >= 1 - LIGHT_BIAS)
		vector_set(result, 0, 1, 0);
	else if (hit_pos->y <= -1 + LIGHT_BIAS)
		vector_set(result, 0, -1, 0);
	else
		vector_set(result, hit_pos->x, 0, hit_pos->z);
}
