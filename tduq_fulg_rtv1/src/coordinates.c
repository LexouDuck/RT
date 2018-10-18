/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:55:50 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/01 02:56:02 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		vec3_polar_to_cartesian(t_vec_3d result, t_vec_3d const src)
{
	t_float		r;
	t_float		sin_lat;

	r = src[0];
	sin_lat = sin(src[2]);
	result[0] = r * sin_lat * cos(src[1]);
	result[2] = r * sin_lat * sin(src[1]);
	result[1] = r * cos(src[2]);
}

/*
** Longitude is East/west, latitude is north/south
*/

void		vec3_cartesian_to_polar(t_vec_3d result, t_vec_3d const src)
{
	t_float		r;
	t_float		tmp;
	t_float		lat;
	t_float		lon;

	r = sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
	if (r == 0.)
	{
		write(2, "null vec3 cannot be converted to polar coordinates\n", 31);
		vec3_set(result, 0., 0., 0.);
		return ;
	}
	tmp = src[0] == 0. ? 0.001 : src[0];
	lon = atan(src[1] / tmp);
	lat = acos(src[2] / r);
	result[0] = r;
	result[1] = lon;
	result[2] = lat;
}
