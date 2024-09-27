/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int			solve_quadratic(t_vector *e, float *root1, float *root2)
{
	float	q;
	float	discrim;

	discrim = e->y * e->y - 4 * e->x * e->z;
	if (discrim < 0)
		return (0);
	else if (discrim == 0)
	{
		*root1 = -0.5 * e->y / e->x;
		*root2 = *root1;
	}
	else
	{
		q = (e->y > 0) ?
			-0.5 * (e->y + sqrt(discrim)) :
			-0.5 * (e->y - sqrt(discrim));
		*root1 = q / e->x;
		*root2 = e->z / q;
	}
	return (1);
}

static inline int	intersect_sphere_inside(t_vector *pos)
{
	return ((
		pos->x * pos->x +
		pos->y * pos->y +
		pos->z * pos->z) >= 1);
}

int					intersect_sphere(t_object *object, t_ray *ray)
{
	t_vector	quadratic;
	float		tmp;
	float		root1;
	float		root2;

	quadratic.x = vector_scalar(&ray->dir, &ray->dir);
	quadratic.y = vector_scalar(&ray->dir, &ray->pos) * 2;
	quadratic.z = vector_scalar(&ray->pos, &ray->pos) - 1;
	if (!object || !solve_quadratic(&quadratic, &root1, &root2))
		return (0);
	if (root1 > root2)
	{
		tmp = root1;
		root1 = root2;
		root2 = tmp;
	}
	if (root1 < 0)
	{
		root1 = root2;
		if (root1 < 0)
			return (0);
	}
	ray->t = root1;
	return (intersect_sphere_inside(&ray->pos));
}

void				getnormal_sphere(
	t_vector *result,
	t_object *object,
	t_vector *hit_pos)
{
	if (!object)
		return ;
	vector_set(result, hit_pos->x, hit_pos->y, hit_pos->z);
}
