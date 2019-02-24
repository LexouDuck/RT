/*
** This function should return TRUE iff objray.t has been updated; ie, iff
**	there is an intersection, and ray.origin is not located within the cylinder.
**
** Rays should arrive already converted to object space coordinates.
**
** The cylinder primitive is centered in (0., 0., 0.) by default, with 1. as
**	default radius, and (0., 1., 0.) as default height. This means the base
**	circle verifies {p = (x, -0.5, z) | x^2 + z^2 <= 1} and the top circle
**	{p = (x, +0.5, z) | x^2 + z^2 <= 1}

static t_intersection		rt_cl_cylinder_intersect
(
							float *		res,
							t_ray		ray
)
{
	t_ray		tmp_ray;
	float		tmp;
	float		new_t;
	bool		is_in_hrz_area;
	bool		is_in_vrt_area;

	if ((is_in_hrz_area = (-0.5 <= ray.pos.y && ray.pos.y <= 0.5)) &&
		(is_in_vrt_area = (vec3_ynull_dot(ray.pos, ray.pos) <= 1.)))
		return (INTER_NONE);
	tmp = 1. / 0.;
	tmp_ray = ray;
	if (rt_cl_infcylinder_intersect(&new_t, tmp_ray))
	{
		if (fabs(tmp_ray.pos.y + tmp_ray.t * tmp_ray.dir.y) < 0.5)
			tmp = tmp_ray.t;
	}
	tmp_ray.t = ray.t;
	tmp_ray.pos.y -= 0.5;
	if (!is_in_hrz_area && intersect_ray_disk(&tmp_ray))
		tmp = fmin(tmp, tmp_ray.t);
	tmp_ray.t = ray.t;
	tmp_ray.pos.y += 1.;
	if (!is_in_hrz_area && intersect_ray_disk(&tmp_ray))
		tmp = fmin(tmp, tmp_ray.t);
	ray.t = fmin(tmp, ray.t);
	*res = tmp;
	return (INTER_OUTSIDE);
}

/*
** Rays should arrive already converted to object space.
**
** Returns both vectors in object space. Note that on the unit infcylinder of
**	R3, every point on the cylinder corresponds to its unit normal, if one sets
**	the y coordinate to 0; as for every point on the cylinder x^2 + z^2 == 1

static float3				rt_cl_cylinder_get_normal
(
							float3		hitpos,
							float3		normal,
							t_ray		ray
)
{
//s	get_ray_hitpos(hitpos, ray);
	if (fabs(hitpos.y - 0.5) < APPROX)
		// vec3_set(normal, 0., 1., 0.);
		return ((float3)(hitpos.x, 1., hitpos.z));
	else if (fabs(hitpos.y + 0.5) < APPROX)
		// vec3_set(normal, 0., -1., 0.);
		return ((float3)(hitpos.x, -1., hitpos.z));
	else
		// vec3_set(normal, hitpos[0], 0., hitpos[2]);
		return ((float3)(hitpos.x, 0., hitpos.z));
}
*/