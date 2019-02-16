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

static uint	rt_cl_rand_bit_shuffle
(
							uint	n
)
{
	uint	offset = n % 32;

	return ((n << (32 - offset)) ^ (n >> offset));
}


uint		rt_cl_rand
(
				__local		uint *	random_seed
)
{
	*random_seed = (CEIL_SQRT_MOD * rt_cl_rand_bit_shuffle(*random_seed) + OFFSET) & MODULUS;
	return (*random_seed);
}


uint		rt_cl_rand_0_to_pow2n
(
				__local 	uint *	random_seed,
							uint	n
)
{
	return (rt_cl_rand(random_seed) & ((0x1 << n) - 1));
}


uint		rt_cl_rand_0_to_n
(
				__local		uint *	random_seed,
							uint	n
)
{
	return (rt_cl_rand(random_seed) % n);
}


int			rt_cl_rand_a_to_b
(
				__local		uint *	random_seed,
							int		a,
							int		b
)
{
	int		res;

	res = (a < b) ?
		rt_cl_rand_0_to_n(random_seed, b - a) + a:
		rt_cl_rand_0_to_n(random_seed, a - b) + b;
	return (res);
}


float		rt_cl_frand_0_to_1
(
				__local		uint *	random_seed
)
{
	return ((float)rt_cl_rand(random_seed) / (float)MODULUS);
}

float		rt_cl_frand_neg1half_to_pos1half
(
				__local		uint *	random_seed
)
{
	return (rt_cl_frand_0_to_1(random_seed) - 1);
}

float		rt_cl_frand_neg1_to_pos1
(
				__local		uint *	random_seed
)
{
	return (2 * rt_cl_frand_neg1half_to_pos1half(random_seed));
}


float		rt_cl_frand_a_to_b
(
				__local		uint *	random_seed,
							float	a,
							float	b
)
{
	float	res = rt_cl_frand_0_to_1(random_seed);

	res *= (a < b) ?
		(b - a) + a:
		(a - b) + b;
	return (res);
}






float3			rt_cl_f3rand_0_to_1
(
				__local		uint *			random_seed	
)
{
	return (float3)(rt_cl_frand_0_to_1(random_seed),
					rt_cl_frand_0_to_1(random_seed),
					rt_cl_frand_0_to_1(random_seed));
}

float3			rt_cl_f3rand_neg1half_to_pos1half
(
				__local		uint *			random_seed	
)
{
	return (float3)(rt_cl_frand_0_to_1(random_seed) - 0.5,
					rt_cl_frand_0_to_1(random_seed) - 0.5,
					rt_cl_frand_0_to_1(random_seed) - 0.5);
}

//TODO add vectorial cos/phong sampling etc
//Add random points on algebraic curves

float3			rt_cl_rand_dir_sphere
(
				__local		uint *			random_seed
)
{
	float radius_cos_th = rt_cl_frand_neg1_to_pos1(random_seed); //rand_-1_to_1 = cos(theta)
    float radius_sin_th = sqrt(1 - radius_cos_th * radius_cos_th); // sin(theta)
    float lon = TAU * rt_cl_frand_0_to_1(random_seed);

    return (float3)(radius_cos_th, cos(lon) * radius_sin_th, sin(lon) * radius_sin_th);
}

/*
** Returns a random vector in a hemisphere defined by 'axis'.
** Axis should already be normalized when this function is called.
*/
float3			rt_cl_rand_dir_hemi
(
				__local		uint *			random_seed,
							float3 const	axis
)
{
	float3		randdir;
	float2		seed;
	float		tmp;
	float3		vtan1;
	float3		vtan2;
	float16		lin_mat;

	seed.x = TAU * rt_cl_frand_0_to_1(random_seed);
	seed.y = rt_cl_frand_0_to_1(random_seed);
	tmp = sqrt((float)(1. - seed.y * seed.y));
	randdir = (float3)(cos(seed.x) * tmp, sin(seed.x) * tmp, seed.y); //TODO convert to sincos ?
	vtan1 = rt_cl_f3rand_neg1half_to_pos1half(random_seed);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = rt_cl_apply_linear_matrix(lin_mat, randdir);
	return (randdir);
}