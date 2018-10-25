/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int		solve_quadratic(t_vector *e, float *t0, float *t1)
{
	float	q;
	float	discrim;

	discrim = e->y * e->y - 4 * e->x * e->z;
	if (discrim < 0)
		return (0);
	else if (discrim == 0)
	{
		*t0 = -0.5 * e->y / e->x;
		*t1 = *t0;
	}
	else
	{
		q = (e->y > 0) ?
			-0.5 * (e->y + sqrt(discrim)) :
			-0.5 * (e->y - sqrt(discrim));
		*t0 = q / e->x;
		*t1 = e->z / q;
	}
	return (1);
}

static float	vector_dot_neg(t_vector *v1, t_vector *v2)
{
	float	result;

	result = 0;
	result += (v1->x * v2->x);
	result -= (v1->y * v2->y);
	result += (v1->z * v2->z);
	return (result);
}

static int		intersect_infinite_cone(t_ray *ray)
{
	t_vector	quadratic;
	float		root1;
	float		root2;

	ray->pos.y += 1;
	quadratic.x = vector_dot_neg(&ray->dir, &ray->dir);
	quadratic.y = vector_dot_neg(&ray->dir, &ray->pos) * 2;
	quadratic.z = vector_dot_neg(&ray->pos, &ray->pos);
	if (!solve_quadratic(&quadratic, &root1, &root2))
		return (0);
	if (root1 <= 0 && root2 <= 0)
		return (0);
	if (root1 <= 0)
		root1 = root2;
	else if (root2 <= 0)
		root2 = root1;
	if (root1 > ray->t && root2 > ray->t)
		return (0);
	if ((ray->dir.y * root1 + ray->pos.y) *
		(ray->dir.y * root2 + ray->pos.y) >= 0)
		ray->t = (root1 < root2) ? root1 : root2;
	else
		ray->t = (root1 > root2) ? root1 : root2;
	return (1);
}

int				intersect_cone(t_object *object, t_ray *ray)
{
	t_ray	tmp;
	float	t;
	int		is_in_infcone;
	int		is_in_hrz_area;

	if ((is_in_infcone = (vector_dot_neg(&ray->pos, &ray->pos) <= 0) &&
		(is_in_hrz_area = (-1 <= ray->pos.y && ray->pos.y <= 1))) || !object)
		return (0);
	t = 1. / 0.;
	tmp = *ray;
	if (intersect_infinite_cone(&tmp))
	{
		t = tmp.pos.y + tmp.t * tmp.dir.y;
		if (0 < t && t < 1)
			t = tmp.t;
		else
			t = 1. / 0.;
	}
	tmp.t = ray->t;
	if (intersect_disk(&tmp, 1, &tmp.t))
		t = (t < tmp.t) ? t : tmp.t;
	ray->t = (t < ray->t) ? t : ray->t;
	return (ray->t == t);
}

void			getnormal_cone(
	t_vector *result,
	t_object *object,
	t_vector *hit_pos)
{
	if (!object)
		return ;
	else if (hit_pos->y >= -LIGHT_BIAS)
	{
		vector_set(result, 0, 1, 0);
	}
	else
	{
		vector_set(result,
			hit_pos->x,
			hit_pos->y,
			hit_pos->z);
		vector_normalize(result);
	}
}
