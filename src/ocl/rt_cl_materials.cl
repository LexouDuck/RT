/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_materials.cl                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Seen in Eric Veach's thesis: phong exponent should be (1/roughness) - 1
*/
static float3	rt_cl_get_dir_in_coslobe_from_axis
(
						uint2 *		random_seeds,
						float3		axis_dir,
						float		roughness
)
{
	float 		phong;

	phong = native_recip(roughness) - 1.f;
	return (rt_cl_rand_dir_coslobe(random_seeds, axis_dir, phong));
}

static float3	rt_cl_get_reflect
(
						float3		incdir,
						float3		normal
)
{
	return (mad(-2.f * dot(incdir, normal), normal, incdir));
}

static float3	rt_cl_get_reflect_coslobe
(
						uint2 *		random_seeds,
						float3		incdir,
						float3		normal,
						float		roughness
)
{
	float3		reflect;

	reflect = rt_cl_get_reflect(incdir, normal);
	if (roughness > 0.f)
		reflect = rt_cl_get_dir_in_coslobe_from_axis(random_seeds, reflect, roughness);
	return (reflect);
}

/*
** Formula for transparency transmitted ray T:
**
** T = 	Tn + Tt
**	 = 	[n1/n2 * (I - dot(I, N) * N)]
**		+
**		[-N   *   sqrt(1 - (n1/n2)^2 * (1 - quadnorm(I, N)))]
**
** with n1 the refractive index for the incidence medium, n2 for refrac_ind of
**		the transmission medium, N the hitpos normal, I the hitpos incidence
**		vector.
*/
static bool		rt_cl_get_transmit
(
						float3 *	res,
						float3		incdir,
						float3		normal,
						float		n1,
						float		n2
)
{
	float3		newdir;
	float		refrac_ratio;
	float		fresnel;
	float		costh_transmit;
	float		dot_i_n;

	dot_i_n = dot(incdir, normal);
	refrac_ratio = n1 / n2;
	fresnel = 1.f - refrac_ratio * refrac_ratio * (1.f - dot_i_n * dot_i_n);
	if (fresnel < 0.f)
	{
		*res = rt_cl_get_reflect(incdir, normal);
		return (false);
	}
	costh_transmit = sqrt(fresnel); //this is cos(theta_transmited), the angle made after transmission)
	//	Tn
	newdir = (float3)refrac_ratio * mad(dot_i_n, -normal, incdir);
	//	+ Tt
	newdir = mad(costh_transmit, -normal, newdir);
	newdir = normalize(newdir);
	*res = newdir;
	return (true);
}

static bool		rt_cl_get_transmit_coslobe
(
						float3 *	res,
						uint2 *		random_seeds,
						float3		incdir,
						float3		normal,
						float		n1,
						float		n2,
						float		roughness
)
{
	float3		transmit;
	bool		is_transmitted;

	is_transmitted = rt_cl_get_transmit(&transmit, incdir, normal, n1, n2);
	if (roughness > 0.f)
		transmit = rt_cl_get_dir_in_coslobe_from_axis(random_seeds, transmit, roughness);
	*res = transmit;
	return (is_transmitted);
}

static bool		rt_cl_get_transmit_or_reflect
(
						float3 *		res,
						uint2 *			random_seeds,
						float3			incdir,
						float3			normal,
						float			n1,
						float			n2,
						float			roughness
)
{
	float3		newdir;
	float		dot_neg_i_n;
	float		schlick;
	float		schlick_r0;
	bool		is_transmitted;

	schlick_r0 = (n1 - n2) / (n1 + n2);
	schlick_r0 = schlick_r0 * schlick_r0;
	dot_neg_i_n = dot(-incdir, normal);
	schlick = schlick_r0 + (1.f - schlick_r0) * pown((float)(1.f - dot_neg_i_n), 5);
	if (rt_cl_frand_0_to_1(random_seeds) > schlick)
	{
		is_transmitted = rt_cl_get_transmit_coslobe(&newdir, random_seeds, incdir, normal, n1, n2, roughness);
	}
	else
	{
		is_transmitted = false;
		newdir = rt_cl_get_reflect_coslobe(random_seeds, incdir, normal, roughness);//rt_cl_get_reflect(incdir, normal);
	}
	*res = newdir;
	return (is_transmitted);
}
