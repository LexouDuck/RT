/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:05:01 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 12:26:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool			get_realroots_quadpoly(t_float *root1, t_float *root2,
									t_vec_3d const quadpoly)
{
	t_float		delta;
	t_float		one_over_two_a;

	delta = quadpoly[1] * quadpoly[1] - 4 * quadpoly[0] * quadpoly[2];
	if (delta < 0.)
	{
		*root1 = 0. / 0.;
		*root2 = 0. / 0.;
		return (FALSE);
	}
	one_over_two_a = 0.5 / quadpoly[0];
	delta = sqrt(delta);
	*root1 = (-quadpoly[1] + delta) * one_over_two_a;
	*root2 = (-quadpoly[1] - delta) * one_over_two_a;
	return (TRUE);
}

/*
** Returns the point on the object hit by a ray in object space coordinates.
*/

inline void		get_ray_hitpos(t_vec_3d hitpos, t_ray const objray)
{
	vec3_scale(hitpos, objray.t, objray.dir);
	vec3_add(hitpos, hitpos, objray.pos);
}

inline void		get_reflect(t_vec_3d res,
						t_vec_3d const incident, t_vec_3d const normal)
{
	vec3_scale(res, -2 * vec3_dot(incident, normal), normal);
	vec3_add(res, res, incident);
}

inline void		print_object(t_object const obj)
{
	printf("type: %d\n"
			"pos: (%f, %f, %f)\n"
			"scl: (%f, %f, %f)\n"
			"rot: (%f, %f, %f)\n"
			"abd: (%f, %f, %f)\n"
			"spc: (%f, %f, %f)\n", obj.type,
			obj.pos[0], obj.pos[1], obj.pos[2],
			obj.scl[0], obj.scl[1], obj.scl[2],
			obj.rot[0], obj.rot[1], obj.rot[2],
			obj.albedo[0], obj.albedo[1], obj.albedo[2],
			obj.specul[0], obj.specul[1], obj.specul[2]);
	print_mat44("o_to_w", obj.o_to_w);
	print_mat44("w_to_o", obj.w_to_o);
	print_mat33("lin_o_to_w", obj.linear_o_to_w);
	print_mat33("lin_w_to_o", obj.linear_w_to_o);
	print_mat33("n_to_w", obj.n_to_w);
}
