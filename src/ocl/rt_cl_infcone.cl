
static t_intersection		rt_cl_infcone_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3 		quadpoly;
	float2		roots;

	quadpoly.x = dot(ray.dir, ray.dir);
	quadpoly.y = 2. * dot(ray.dir, ray.pos);
	quadpoly.z = dot(ray.pos, ray.pos) - 1.;
	if(!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
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


static inline float		vec3_yneg_dot
(							float3 v1, 
							float3 v2
)
{
	return (v1.x * v2.x - v1.y * v2.y + v1.z * v2.z);
}

static float3			rt_cl_infcone_get_normal
(
						float3 hitpos
)
{
	return (hitpos);
}
