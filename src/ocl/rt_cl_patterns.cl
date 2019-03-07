static void			rt_cl_get_pattern_horizontal_waves
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = cos((float)(uvw_pos.x * TWOTAU * uvw_scale.x));
	return ;
}

static void			rt_cl_get_pattern_vertical_waves
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = cos((float)(uvw_pos.y * TWOTAU * uvw_scale.y));
	return ;
}

static void			rt_cl_get_pattern_double_waves
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = cos((float)(uvw_pos.x * TWOTAU * uvw_scale.x))
				* cos((float)(uvw_pos.y * TWOTAU * uvw_scale.y));
	return ;
}

static void			rt_cl_get_pattern_horizontal_stripes
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	if (fmod((float)((uvw_pos.x) * uvw_scale.x), 0.4f) < 0.2f)
		*texel_value = 1.f;
	else
		*texel_value = 0;
	return ;
}

static void			rt_cl_get_pattern_vertical_stripes
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	if (fmod((float)((uvw_pos.y) * uvw_scale.y), 0.4f) < 0.2f)
		*texel_value = 1.f;
	else
		*texel_value = 0;
	return ;
}

static void			rt_cl_get_pattern_checkerboard
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	if (fmod((float)(uvw_pos.x * uvw_scale.x), 0.4f) < 0.2f
		^ fmod((float)(uvw_pos.y * uvw_scale.y), 0.4f) < 0.2f)
	{
		if (fmod((float)(uvw_pos.z * uvw_scale.z), 0.4f) < 0.2f)
			*texel_value = 1.f;
		else
			*texel_value = 0.f;
	}
	else
	{
		if (fmod((float)(uvw_pos.z * uvw_scale.z), 0.4f) < 0.2f)
			*texel_value = 0.f;
		else
			*texel_value = 1.f;
	}
	return ;
}

static void			rt_cl_get_pattern_perlin
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = rt_cl_perlin_noise_3d(uvw_pos * 4.f, 0.4f, 6, 42);
	return ;
}

static void			rt_cl_get_pattern_wood
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = (sin((float)(uvw_pos.x + rt_cl_perlin_noise_3d(uvw_pos * 4.f, 0.4f, 6, 42) * 100) * TAU * 0.02f)) * 0.5f;
	return ;
}