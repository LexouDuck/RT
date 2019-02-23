static t_intersection		rt_cl_sphere_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3		quadpoly;
	float2		roots;

	quadpoly.x = dot(ray.dir, ray.dir);
	quadpoly.y = 2. * dot(ray.dir, ray.pos);
	quadpoly.z = dot(ray.pos, ray.pos) - 1.;
	if (!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if ((roots.x <= 0. && roots.y <= 0.) ||
		(roots.x > ray.t && roots.y > ray.t))
		return (INTER_NONE);
	else if (roots.x <= 0.)
	{
		*res = roots.y;
		return (INTER_INSIDE);
	}
	else if (roots.y <= 0.)
	{
		*res = roots.x;
		return (INTER_INSIDE);
	}
	else
	{
		*res = fmin(roots.x, roots.y);
		return (INTER_OUTSIDE);
	}
}

static float3			rt_cl_sphere_get_normal(float3 hitpos)
{
	return (hitpos);
}

static float3			rt_cl_sphere_get_random_point
(
							uint2 *			random_seeds
)
{
	float radius_cos_th = rt_cl_frand_neg1_to_pos1(random_seeds); //rand_-1_to_1 = cos(theta)
    float radius_sin_th = sqrt(1 - radius_cos_th * radius_cos_th); // sin(theta)
    float lon = TAU * rt_cl_frand_0_to_1(random_seeds);

    return (float3)(radius_cos_th, cos(lon) * radius_sin_th, sin(lon) * radius_sin_th);
}