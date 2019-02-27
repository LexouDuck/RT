static t_intersection		rt_cl_infcone_intersect
(
							float *		res,
							t_ray		ray
)
{
	float3 			quadpoly;
	float2			roots;
	bool			ray_hrz_orient;

	quadpoly.x = rt_cl_float3_yneg_dot(ray.dir, ray.dir);
	quadpoly.y = 2. * rt_cl_float3_yneg_dot(ray.dir, ray.pos);
	quadpoly.z = rt_cl_float3_yneg_dot(ray.pos, ray.pos);
	if(!(rt_cl_get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if (roots.x <= 0. && roots.y <= 0.)
		return (INTER_NONE);
	ray_hrz_orient = (ray.dir.y * roots.x + ray.pos.y) *
					(ray.dir.y * roots.y + ray.pos.y) >= 0.;
	if (roots.x <= 0.)
	{
		*res = roots.y;
		return (ray_hrz_orient ? INTER_INSIDE : INTER_OUTSIDE);
	}
	else if (roots.y <= 0.)
	{
		*res = roots.x;
		return (ray_hrz_orient ? INTER_INSIDE : INTER_OUTSIDE);
	}
	*res = fmin(roots.x, roots.y);
	return (ray_hrz_orient ? INTER_OUTSIDE : INTER_INSIDE);
}

static float3			rt_cl_infcone_get_normal
(
						float3 hitpos
)
{
	float3 	normal;

	normal = (float3)(hitpos.x, - hitpos.y, hitpos.z);	
	normal = normalize(normal);

	return (normal);
}
