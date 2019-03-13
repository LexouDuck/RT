/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_random.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
** ************************************************************************** *|
**                          Random Number Generator                           *|
** ************************************************************************** *|
*/

/*
** Random number generator. Modulus is 2^31
**
** - OFFSET and MODULUS are mutually prime.
** - CEIL_SQRT_MOD % 4 should be = 1 because MODULUS is a multiple of 4
** - For all P prime divisors of MODULUS, a % p = 1
** - OFFSET should be small compared to the two other parameters
** - The bitwise & is applied, which explains the choice of modulus to be
**		2^31 - 1 in implementation (could also be called RAND_MAX)
**
** Basic RNG formula is:
**		new_nb = (CEIL_SQRT_MOD  * old_nb + OFFSET) % MODULUS
*/

static uint		rt_cl_rand
(
							uint2 *		rand_s
)
{	/* hash the seeds using bitwise AND operations and bitshifts */
//	rand_s->x = 36969 * (rand_s->x >> 16) + ((28343 * rand_s->x) & 0xFFFF);  
//	rand_s->y = 18000 * (rand_s->y >> 16) + ((45612 * rand_s->y) & 0xFFFF);
	rand_s->x = 36969 * (rand_s->x & 0xFFFF) + (rand_s->x >> 16);  
	rand_s->y = 18000 * (rand_s->y & 0xFFFF) + (rand_s->y >> 16);
	uint n = (rand_s->x << 16) + (rand_s->y);

	return n;
}

static uint			rt_cl_rand_0_to_pow2n
(
						 	uint2 *			random_seeds,
							uint			n
)
{
	return (rt_cl_rand(random_seeds) & ((0x1 << n) - 1));
}

static uint			rt_cl_rand_0_to_n
(
							uint2 *			random_seeds,
							uint			n
)
{
	return (rt_cl_rand(random_seeds) % n);
}


static int			rt_cl_rand_a_to_b
(
							uint2 *			random_seeds,
							int				a,
							int				b
)
{
	int		res;
	int		infbound = min(a, b);
	int		supbound = max(a, b);

	res = rt_cl_rand_0_to_n(random_seeds, supbound - infbound) + infbound;
	return (res);
}


static float		rt_cl_frand_0_to_1
(
							uint2 *			random_seeds
)
{
	int n;

	n = rt_cl_rand(random_seeds);

	union
	{
		float f;
		uint ui;
	}
	fui;

	fui.ui = (n & 0x007fffff) | 0x3F800000; /*extract mantissa and set exponent to have 1. < fui.f < 2.*/
	return (fui.f - 1.f);
}

static float		rt_cl_frand_neg1half_to_pos1half
(
							uint2 *			random_seeds
)
{
	return (rt_cl_frand_0_to_1(random_seeds) - 0.5f);
}

static float		rt_cl_frand_neg1_to_pos1
(
							uint2 *			random_seeds
)
{
	return (2 * rt_cl_frand_neg1half_to_pos1half(random_seeds));
}


static float		rt_cl_frand_a_to_b
(
							uint2 *		random_seeds,
							float		a,
							float		b
)
{
	float	res = rt_cl_frand_0_to_1(random_seeds);
	float	infbound = fmin(a, b);
	float	supbound = fmax(a, b);

	res *= (supbound - infbound);
	res += infbound;
	return (res);
}



static float3			rt_cl_f3rand_0_to_1
(
							uint2 *			random_seeds
)
{
	return (float3)(rt_cl_frand_0_to_1(random_seeds),
					rt_cl_frand_0_to_1(random_seeds),
					rt_cl_frand_0_to_1(random_seeds));
}

static float3			rt_cl_f3rand_neg1half_to_pos1half
(
							uint2 *			random_seeds	
)
{
	return (float3)(rt_cl_frand_0_to_1(random_seeds) - 0.5f,
					rt_cl_frand_0_to_1(random_seeds) - 0.5f,
					rt_cl_frand_0_to_1(random_seeds) - 0.5f);
}



//TODO add vectorial cos/phong sampling etc

/*
** Returns a random vector in a hemisphere defined by 'axis'.
** Axis should already be normalized when this function is called.
*/
static float3			rt_cl_rand_dir_hemi
(
							uint2 *			random_seeds,
							float3			axis
)
{
	float3		randdir;
	float2		seed;
	float		tmp;
	float3		vtan1;
	float3		vtan2;
	float16		lin_mat;

	seed.x = TAU * rt_cl_frand_0_to_1(random_seeds);
	seed.y = rt_cl_frand_0_to_1(random_seeds);
	tmp = sqrt((float)(1.f - seed.y * seed.y));
	randdir = (float3)(cos(seed.x) * tmp, sin(seed.x) * tmp, seed.y); //TODO convert to sincos ?
	vtan1 = rt_cl_f3rand_neg1half_to_pos1half(random_seeds);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = rt_cl_apply_linear_matrix(lin_mat, randdir);
//	randdir = normalize(randdir); //useless because of orthonormality of lin_mat
	return (randdir);
}

static float3			rt_cl_rand_dir_coshemi
(
							uint2 *			random_seeds,
							float3			axis
)
{
	float3		randdir;
	float2		seed;
	float		tmp;
	float3		vtan1;
	float3		vtan2;
	float16		lin_mat;
//	float2		sincos_th;

	seed.x = TAU * rt_cl_frand_0_to_1(random_seeds);
	seed.y = rt_cl_frand_0_to_1(random_seeds);
	tmp = sqrt((float)(1.f - seed.y));
//	sincos_th.x = sincos(seed.x, &(sincos_th.y));
//	randdir = (float3)(sincos_th.y * tmp, sincos_th.x * tmp, sqrt(seed.y));
	randdir = (float3)(cos(seed.x) * tmp, sin(seed.x) * tmp, sqrt(seed.y));
	vtan1 = rt_cl_f3rand_neg1half_to_pos1half(random_seeds);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = rt_cl_apply_linear_matrix(lin_mat, randdir);
//	randdir = normalize(randdir); //useless because of orthonormality of lin_mat
	return (randdir);
}

static float3			rt_cl_rand_dir_coslobe
(
							uint2 *			random_seeds,
							float3			axis,
							float			phong
)
{
	float3		randdir;
	float2		seed;
	float		tmp;
	float3		vtan1;
	float3		vtan2;
	float16		lin_mat;
	float		phongexp;

	phongexp = native_recip(phong + 1.f);//TODO isn't this just 'roughness' ?
	seed.x = TAU * rt_cl_frand_0_to_1(random_seeds);
	seed.y = rt_cl_frand_0_to_1(random_seeds);
	//TODO can be done with single call to powr, (e^2x) = e^x^2 = e^x * e^x
	tmp = sqrt((float)(1.f - powr(seed.y, 2.f * phongexp)));
	randdir = (float3)(cos(seed.x) * tmp, sin(seed.x) * tmp, powr(seed.y, phongexp));
	vtan1 = rt_cl_f3rand_neg1half_to_pos1half(random_seeds);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = rt_cl_apply_linear_matrix(lin_mat, randdir);
//	randdir = normalize(randdir); //useless because of orthonormality of lin_mat
	return (randdir);
}

#if 0
static float3			rt_cl_rand_dir_coslobe
(
							uint2 *			random_seeds,
							float3			axis,
							float			roughness
)
{
	float3		randdir;
	float2		seed;
	float2		sincos_th;
	float		tmp;
	float3		vtan1;
	float3		vtan2;
	float16		lin_mat;
	float		phongexp;

	seed.x = TAU * rt_cl_frand_0_to_1(random_seeds);
	seed.y = rt_cl_frand_0_to_1(random_seeds);
	phongexp = native_powr(seed.y, roughness);
	tmp = sqrt((float)(1.f - phongexp * phongexp));
	sincos_th.x = sincos(seed.x, &(sincos_th.y));
	randdir = (float3)(sincos_th.y * tmp, sincos_th.x * tmp, phongexp);
	vtan1 = fabs(axis.x) < EPS ? (float3)(1.f, 0.f, 0.f) : (float3)(0.f, 0.f, 1.f);//rt_cl_f3rand_neg1half_to_pos1half(random_seeds);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = rt_cl_apply_linear_matrix(lin_mat, randdir);
//	randdir = normalize(randdir); //useless because of orthonormality of lin_mat
	return (randdir);
}
#endif
