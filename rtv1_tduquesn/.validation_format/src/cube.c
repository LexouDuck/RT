/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 16:54:51 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 12:50:11 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_float				vec3_supm_norm(t_vec_3d const v)
{
	t_float		sup;
	t_float		tmp;

	sup = ft_fabs(v[0]);
	tmp = ft_fabs(v[1]);
	sup = ft_fmax(tmp, sup);
	tmp = ft_fabs(v[2]);
	return (ft_fmax(tmp, sup));
}

/*
** 0 is 90 degree rotation around the z axis
** 1 is 90 degree rotation around the x axis
** 2 is 90 degree rotation around the y axis
*/

static void			ray_coordinate_swap(t_ray *ray, t_float t, int i, int neg)
{
	t_float		tmp;
	int			j;

	j = i + 1;
	if (j == 3)
		j = 0;
	ray->pos[1] += neg ? 0.5 : -0.5;
	tmp = ray->pos[i];
	ray->pos[i] = -ray->pos[j];
	ray->pos[j] = tmp;
	ray->pos[1] += neg ? -0.5 : 0.5;
	tmp = ray->dir[i];
	ray->dir[i] = -ray->dir[j];
	ray->dir[j] = tmp;
	ray->t = t;
}

t_bool				intersect_ray_cube(t_ray *objray)
{
	t_ray	ray_tmp;
	t_float	tmp;

	if (vec3_supm_norm(objray->pos) <= 0.5)
		return (FALSE);
	tmp = 1. / 0.;
	ray_tmp = *objray;
	ray_tmp.pos[1] -= 0.5;
	tmp = ft_fmin(tmp, intersect_ray_square(&ray_tmp) ? ray_tmp.t : 1. / 0.);
	ray_coordinate_swap(&ray_tmp, objray->t, 0, TRUE);
	tmp = ft_fmin(tmp, intersect_ray_square(&ray_tmp) ? ray_tmp.t : 1. / 0.);
	ray_coordinate_swap(&ray_tmp, objray->t, 1, TRUE);
	tmp = ft_fmin(tmp, intersect_ray_square(&ray_tmp) ? ray_tmp.t : 1. / 0.);
	ray_coordinate_swap(&ray_tmp, objray->t, 2, TRUE);
	ray_tmp = *objray;
	ray_tmp.pos[1] += 0.5;
	tmp = ft_fmin(tmp, intersect_ray_square(&ray_tmp) ? ray_tmp.t : 1. / 0.);
	ray_coordinate_swap(&ray_tmp, objray->t, 0, FALSE);
	tmp = ft_fmin(tmp, intersect_ray_square(&ray_tmp) ? ray_tmp.t : 1. / 0.);
	ray_coordinate_swap(&ray_tmp, objray->t, 1, FALSE);
	tmp = ft_fmin(tmp, intersect_ray_square(&ray_tmp) ? ray_tmp.t : 1. / 0.);
	ray_coordinate_swap(&ray_tmp, objray->t, 2, FALSE);
	objray->t = ft_fmin(tmp, objray->t);
	return (objray->t == tmp);
}

void				get_hnn_cube(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray)
{
	get_ray_hitpos(hitpos, objray);
	if (ft_fabs(hitpos[0] - 0.5) <= APPROX)
		vec3_set(normal, 1., 0., 0.);
	else if (ft_fabs(hitpos[0] + 0.5) <= APPROX)
		vec3_set(normal, -1., 0., 0.);
	else if (ft_fabs(hitpos[1] - 0.5) <= APPROX)
		vec3_set(normal, 0., 1., 0.);
	else if (ft_fabs(hitpos[1] + 0.5) <= APPROX)
		vec3_set(normal, 0., -1., 0.);
	else if (ft_fabs(hitpos[2] - 0.5) <= APPROX)
		vec3_set(normal, 0., 0., 1.);
	else if (ft_fabs(hitpos[2] + 0.5) <= APPROX)
		vec3_set(normal, 0., 0., -1.);
	else
		vec3_set(normal, 0., 0., 0.);
}
