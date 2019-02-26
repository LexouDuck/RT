static inline float			rt_cl_float3_yneg_dot
(							float3 v1, 
							float3 v2
)
{
	return (v1.x * v2.x - v1.y * v2.y + v1.z * v2.z);
}

static t_intersection		rt_cl_cone_intersect
(
							float *		res,
							t_ray		ray
)
{
	t_ray		tmp_ray;
	t_float		tmp;
	t_bool		is_in_infcone;
	t_bool		is_in_hrz_area;

	if ((is_in_infcone = ( rt_cl_float3_yneg_dot(ray.pos, ray.pos) <= 0) &&
		(is_in_hrz_area = (0. <= ray.pos.y && ray.pos.y <= 1.))))
		return(INTERS_NONE)
	tmp = 1. / 0.;
	tmp_ray= ray;
	if (rt_cl_infcone_intersect(&tmp_ray))
	{
		tmp = tmp_ray.pos.y + tmp_ray.dir.y;
		tmp= 0. < tmp && tmp < 1. ? tmp_ray.t 1. /0.;
	}
	tmp_ray.t = ray.t
}