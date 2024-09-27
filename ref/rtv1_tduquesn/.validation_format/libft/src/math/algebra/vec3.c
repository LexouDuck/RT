/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 02:13:00 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/17 00:07:35 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_algebra.h"

void		vec3_set(t_vec_3d result, t_float x, t_float y, t_float z)
{
	result[0] = x;
	result[1] = y;
	result[2] = z;
}

void		vec3_cpy(t_vec_3d dest, t_vec_3d const src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

void		vec3_swap(t_vec_3d v1, t_vec_3d v2)
{
	t_vec_3d	tmp;

	tmp[0] = v2[0];
	tmp[1] = v2[1];
	tmp[2] = v2[2];
	v2[0] = v1[0];
	v2[1] = v1[1];
	v2[2] = v1[2];
	v1[0] = tmp[0];
	v1[1] = tmp[1];
	v1[2] = tmp[2];
}
