static t_intersection		rt_cl_infcone_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3 		quadpoly;
	float2		roots;

	quadpoly.x = rt_cl_float3_yneg_dot(ray.dir, ray.dir);
	quadpoly.y = 2. * rt_cl_float3_yneg_dot(ray.dir, ray.pos);
	quadpoly.z = rt_cl_float3_yneg_dot(ray.pos, ray.pos);
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
//	if (roots.x > ray.t && roots.y > ray.t)
//		return (INTER_OUTSIDE);
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

static float3			rt_cl_infcone_get_normal
(
						float3 hitpos
)
{
	return ((float3)(hitpos.x, 0, hitpos.y));
}
