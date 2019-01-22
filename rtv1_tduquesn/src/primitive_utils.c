/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 01:05:01 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/21 17:31:26 by fulguritu        ###   ########.fr       */
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

inline void		print_object(t_object const obj)
{
	printf("type: %d\n"
			"material: %d\n"
			"pos: (%f, %f, %f)\n"
			"scl: (%f, %f, %f)\n"
			"rot: (%f, %f, %f)\n"
			"rgb: (%f, %f, %f)\n"
			"spc: (%f, %f, %f)\n",
			obj.type, obj.material,
			obj.pos[0], obj.pos[1], obj.pos[2],
			obj.scl[0], obj.scl[1], obj.scl[2],
			obj.rot[0], obj.rot[1], obj.rot[2],
			obj.rgb.val.r, obj.rgb.val.g, obj.rgb.val.b,
			obj.specul[0], obj.specul[1], obj.specul[2]);
	print_mat44("o_to_w", obj.o_to_w);
	print_mat44("w_to_o", obj.w_to_o);
	print_mat33("lin_o_to_w", obj.linear_o_to_w);
	print_mat33("lin_w_to_o", obj.linear_w_to_o);
	print_mat33("n_to_w", obj.n_to_w);
}
