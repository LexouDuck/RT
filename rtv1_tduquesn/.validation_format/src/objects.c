/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:50:29 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 14:22:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_inter_func		get_inter_func(t_objtype const type)
{
	t_inter_func	res;

	res = type == sphere ? &intersect_ray_sphere : NULL;
	res = type == plane ? &intersect_ray_plane : res;
	res = type == infcone ? &intersect_ray_infcone : res;
	res = type == infcylinder ? &intersect_ray_infcylinder : res;
	res = type == disk ? &intersect_ray_disk : res;
	res = type == square ? &intersect_ray_square : res;
	res = type == triangle ? &intersect_ray_triangle : res;
	res = type == cone ? &intersect_ray_cone : res;
	res = type == cylinder ? &intersect_ray_cylinder : res;
	res = type == paraboloid ? &intersect_ray_paraboloid : res;
	res = type == saddle ? &intersect_ray_saddle : res;
	res = type == cube ? &intersect_ray_cube : res;
	return (res);
}

static t_hnn_func		get_hnn_func(t_objtype const type)
{
	t_hnn_func	res;

	res = type == sphere ? &get_hnn_sphere : NULL;
	res = type == infcone ? &get_hnn_infcone : res;
	res = type == infcylinder ? &get_hnn_infcylinder : res;
	res = type == cone ? &get_hnn_cone : res;
	res = type == cylinder ? &get_hnn_cylinder : res;
	res = type == plane || type == disk || type == square || type == triangle ?
			get_hnn_plane : res;
	res = type == paraboloid ? &get_hnn_paraboloid : res;
	res = type == saddle ? &get_hnn_saddle : res;
	res = type == cube ? &get_hnn_cube : res;
	return (res);
}

void					build_obj(t_object *obj, t_objtype type)
{
	t_mat_3b3	rot;
	t_mat_3b3	tmp;

	obj->type = type;
	obj->intersect = get_inter_func(type);
	obj->get_hnn = get_hnn_func(type);
	mat33_rot(rot, obj->rot[0], 0);
	mat33_rot(tmp, obj->rot[1], 1);
	mat33_mul(rot, tmp, rot);
	mat33_rot(tmp, obj->rot[2], 2);
	mat33_mul(rot, tmp, rot);
	mat33_set_diagmat(tmp, obj->scl);
	mat33_mul(rot, rot, tmp);
	mat33_inv(tmp, rot);
	mat33_cpy(obj->linear_o_to_w, rot);
	mat33_cpy(obj->linear_w_to_o, tmp);
	mat44_set(obj->o_to_w, rot, (t_vec_3d){0, 0, 0},
					(t_vec_4d){obj->pos[0], obj->pos[1], obj->pos[2], 1.});
	mat44_inv(obj->w_to_o, obj->o_to_w);
	mat33_set(obj->n_to_w,
		(t_vec_3d){obj->w_to_o[0], obj->w_to_o[4], obj->w_to_o[8]},
		(t_vec_3d){obj->w_to_o[1], obj->w_to_o[5], obj->w_to_o[9]},
		(t_vec_3d){obj->w_to_o[2], obj->w_to_o[6], obj->w_to_o[10]});
	print_object(*obj);
}
