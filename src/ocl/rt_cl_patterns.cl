static void			rt_cl_get_pattern_horizontal_waves
(
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = cos((float)(uvw_pos.x * TWOTAU * uvw_scale.x * 2.f));
	return ;
}

static void			rt_cl_get_pattern_vertical_waves
(
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = cos((float)(uvw_pos.y * TWOTAU * uvw_scale.y * 2.f));
	return ;
}

static void			rt_cl_get_pattern_double_waves
(
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = cos((float)(uvw_pos.x * TWOTAU * uvw_scale.x * 2.f))
				* cos((float)(uvw_pos.y * TWOTAU * uvw_scale.y * 2.f));
	return ;
}

static void			rt_cl_get_pattern_horizontal_stripes
(
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	if (fmod((float)((uvw_pos.x) * uvw_scale.x), 0.2f) < 0.1f)
		*texel_value = 1.f;
	else
		*texel_value = 0;
	return ;
}

static void			rt_cl_get_pattern_vertical_stripes
(
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	if (fmod((float)((uvw_pos.y) * uvw_scale.y), 0.2f) < 0.1f)
		*texel_value = 1.f;
	else
		*texel_value = 0;
	return ;
}

static void			rt_cl_get_pattern_checkerboard
(
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
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = rt_cl_perlin_noise_3d(uvw_pos * uvw_scale * 8.f, 0.4f, 6, 42);
	return ;
}

static void			rt_cl_get_pattern_wood
(
								float3		uvw_pos,
								float3		uvw_scale,
								float		*texel_value
)
{
	*texel_value = sin((float)(uvw_pos.x * uvw_scale.x + rt_cl_perlin_noise_3d(uvw_pos * uvw_scale * 4.f, 0.4f, 6, 42) * 100.f) * PI * 0.02f) * 0.75f;
	return ;
}