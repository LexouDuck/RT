static inline float		float3_yneg_dot
(							float3 v1, 
							float3 v2
)
{
	return (v1.x * v2.x - v1.y * v2.y + v1.z * v2.z);
}

static t_intersection		rt_cl_hyperboloid_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3 		quadpoly;
	float2		roots;

	quadpoly.x = float3_yneg_dot(ray.dir, ray.dir);
	quadpoly.y = 2. * float3_yneg_dot(ray.dir, ray.pos);
	quadpoly.z = float3_yneg_dot(ray.pos, ray.pos) - 1.;
	if(!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if (roots.x <= 0. && roots.y <= 0.)
		return (INTER_NONE);
	if (roots.x <= 0.)
	{
		*res = roots.y;
		return (INTER_OUTSIDE);
		
	}
	else if (roots.y <= 0.)
	{
		*res = roots.x;
		return (INTER_OUTSIDE);
	}
	if (roots.x > ray.t && roots.y > ray.t)
		return (INTER_OUTSIDE);
	if ((ray.dir.y * roots.x + ray.pos.y) *
		(ray.dir.y * roots.y + ray.pos.y) >= 0.)
	{
		*res = fmin(roots.x, roots.y);
		return(INTER_OUTSIDE);
	
	}
	else
		*res = fmax(roots.x, roots.y);
	return (INTER_INSIDE);
}



static float3			rt_cl_herperboloid_get_normal
(
						float3 hitpos
)
{
	return (hitpos);
}
