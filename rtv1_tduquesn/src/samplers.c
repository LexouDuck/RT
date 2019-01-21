/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   samplers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 03:16:19 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/21 04:49:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Returns a random vector in a hemisphere defined by 'axis'.
*/
static void			vec3_rand_hemi(t_vec_3d randdir, t_vec_3d const axis)
{
	t_float		t1;
	t_float		t2;
	t_float		tmp;
	t_vec_3d	vtan1;
	t_vec_3d	vtan2;

	t1 = TAU * ft_frand_0_to_1();
	t2 = ft_frand_0_to_1();
	tmp = sqrt(1. - t2 * t2);
	vec3_set(randdir, cos(t1) * tmp, sin(t1) * tmp, t2);
	vec3_set(vtan1, ft_frand_0_to_1() - 0.5,
				ft_frand_0_to_1() - 0.5, ft_frand_0_to_1() - 0.5);
	vec3_cross(vtan1, axis, vtan1);
	vec3_eucl_nrmlz(vtan1, vtan1);
	vec3_cross(vtan2, vtan1, axis);
	vec3_set(randdir,
	randdir[0] * vtan1[0] + randdir[1] * vtan2[0] + randdir[2] * axis[0], 
	randdir[0] * vtan1[1] + randdir[1] * vtan2[1] + randdir[2] * axis[1],
	randdir[0] * vtan1[2] + randdir[1] * vtan2[2] + randdir[2] * axis[2]);

}


/*
** Returns a random vector with a cos-biased probability around a given axis.
** Ie, the random vector is more likely to be rather colinear with the axis;
** and is bounded on a hemisphere. The axis is generally a normal or a
** direction between two objects.
**
** PDF p, p(theta) = cos(theta)/PI
*/
static void			vec3_rand_coshemi(t_vec_3d randdir, t_vec_3d const axis)
{
	t_float		t1;
	t_float		t2;
	t_float		tmp;
	t_vec_3d	vtan1;
	t_vec_3d	vtan2;

	t1 = TAU * ft_frand_0_to_1();
	t2 = ft_frand_0_to_1();
	tmp = sqrt(1. - t2);
	vec3_set(randdir, cos(t1) * tmp, sin(t1) * tmp, sqrt(t2));
	vec3_set(vtan1, ft_frand_0_to_1() - 0.5,
				ft_frand_0_to_1() - 0.5, ft_frand_0_to_1() - 0.5);
	vec3_cross(vtan1, axis, vtan1);
	vec3_eucl_nrmlz(vtan1, vtan1);
	vec3_cross(vtan2, vtan1, axis);
	vec3_set(randdir,
	randdir[0] * vtan1[0] + randdir[1] * vtan2[0] + randdir[2] * axis[0], 
	randdir[0] * vtan1[1] + randdir[1] * vtan2[1] + randdir[2] * axis[1],
	randdir[0] * vtan1[2] + randdir[1] * vtan2[2] + randdir[2] * axis[2]);
}

//TODO maybe an optimization with pow(t2, 2) and t2*t2.
static void			vec3_rand_coslobe(t_vec_3d randdir, t_vec_3d const axis,
										t_u32 phong)
{
	t_float		t1;
	t_float		t2;
	t_float		tmp;
	t_float		phongexp;
	t_vec_3d	vtan1;
	t_vec_3d	vtan2;

	phongexp = 1. / (phong + 1);
	t1 = TAU * ft_frand_0_to_1();
	t2 = ft_frand_0_to_1();
	tmp = sqrt(1. - pow(t2, 2. * phongexp));
	vec3_set(randdir, cos(t1) * tmp, sin(t1) * tmp, pow(t2, phongexp));
	vec3_set(vtan1, ft_frand_0_to_1() - 0.5,
				ft_frand_0_to_1() - 0.5, ft_frand_0_to_1() - 0.5);
	vec3_cross(vtan1, axis, vtan1);
	vec3_eucl_nrmlz(vtan1, vtan1);
	vec3_cross(vtan2, vtan1, axis);
	vec3_set(randdir,
	randdir[0] * vtan1[0] + randdir[1] * vtan2[0] + randdir[2] * axis[0], 
	randdir[0] * vtan1[1] + randdir[1] * vtan2[1] + randdir[2] * axis[1],
	randdir[0] * vtan1[2] + randdir[1] * vtan2[2] + randdir[2] * axis[2]);
}

/*
** The input ray 'fxd_pos' should have pos, t, and depth set.
*/

t_ray_sample		ray_sample_init_w_fixed_origin(
							t_ray const fxd_pos,
							t_vec_3d const axis,
							t_u32 const phong)
{
	t_ray_sample	rsamp;
	t_u32 			i;
//	t_float			theta_max;

	i = 0;
	while (i < RAY_SAMPLE_NB)
	{	
		rsamp.rays[i] = fxd_pos;
		++(rsamp.rays[i].sray_depth);
		if (phong == 0)
		{
			vec3_rand_hemi(rsamp.rays[i].dir, axis);
			rsamp.probs[i] = INV_TAU;
		}
		else if (phong == 1)
		{	
			vec3_rand_coshemi(rsamp.rays[i].dir, axis);
			rsamp.probs[i] = vec3_dot(rsamp.rays[i].dir, axis) * INV_PI;
		}
		else
		{
			vec3_rand_coslobe(rsamp.rays[i].dir, axis, phong);//compare with math.h exp()
			rsamp.probs[i] = pow(vec3_dot(rsamp.rays[i].dir, axis), phong)//ft_lfpowi(vec3_dot(rsamp.rays[i].dir, axis), phong)
								* INV_TAU * (phong + 1);
		}
		rsamp.lum[i].val = (t_rgb){0., 0., 0.};
		++i;
	}
	return (rsamp);
}
