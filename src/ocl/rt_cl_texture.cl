static float		rt_cl_rawnoise
(
					uint	n
)
{
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

static float		rt_cl_noise_2d
(
					uint2	pos,
					int		octave,
					uint	seed
)
{
    return (rt_cl_rawnoise(pos.x * 1619 + pos.y * 31337 + octave * 3463 + seed * 13397));
}

static float		rt_cl_interpolate
(
					float2	range,
					float	x
)
{
	float	f;

	f = (1 - cos((float)(x * PI))) * 0.5;
	return (range.x * (1 - f) + range.y * f);
}


static float		rt_cl_smooth_noise_2d
(
					float2	pos,
					uint	octave,
					uint	seed
)
{
	uint2	int_pos;
	float2	frac;
	float2	st_pos;
	float2	uv_pos;
	float2	level;

	int_pos.x = (int)pos.x;
	frac.x = pos.x - int_pos.x;
	int_pos.y = (int)pos.y;
	frac.y = pos.y - int_pos.y;
	st_pos.x = rt_cl_noise_2d(int_pos, octave, seed);
	st_pos.y = rt_cl_noise_2d((uint2)(int_pos.x + 1, int_pos.y), octave, seed);
	uv_pos.x = rt_cl_noise_2d((uint2)(int_pos.x, int_pos.y + 1), octave, seed);
	uv_pos.y = rt_cl_noise_2d((uint2)(int_pos.x + 1, int_pos.y + 1), octave, seed);
	level.x = rt_cl_interpolate(st_pos, frac.x);
	level.y = rt_cl_interpolate(uv_pos, frac.x);
	return (rt_cl_interpolate(level, frac.y));
}

static float		rt_cl_perlin_noise_2d
(
					float2	pos,
					float	persistence,
					uint	octaves,
					uint	seed
)
{
	float	total = 0.0;
	float	frequency = 1.0;
	float	amplitude = 1.0;

	for (uint i = 0; i < octaves; i++)
	{
		total += rt_cl_smooth_noise_2d((float2)(pos.x * frequency, pos.y * frequency), i, seed) * amplitude;
		frequency /= 2;
		amplitude *= persistence;
	}
	return (total);
}

static float2		rt_cl_get_uv_position
(
					__constant	t_object *	obj,
								float3		hitpos
)
{
	float2	uv_pos;

	if (obj->uv_projection == spherical)
		uv_pos= (float2)((0.5f + atan2((float)(hitpos.z), (float)(hitpos.x)) * (0.5f * INV_PI)),
		(0.5f - asin((float)(hitpos.y)) * INV_PI));
	else if (obj->uv_projection == cubic)
	{
		if (fabs((float)(hitpos.x - 1.f)) <= EPS)
			uv_pos = (float2)(((hitpos.z + 1.f) * 0.5f),
			((hitpos.y + 1.f) * 0.5f));
		else if (fabs((float)(hitpos.x + 1.f)) <= EPS)
			uv_pos = (float2)(((-hitpos.z + 1.f) * 0.5f),
			((hitpos.y + 1.f) * 0.5f));
		else if (fabs((float)(hitpos.y - 1.f)) <= EPS)
			uv_pos = (float2)(((hitpos.x + 1.f) * 0.5f),
			((hitpos.z + 1.f) * 0.5f));
		else if (fabs((float)(hitpos.y + 1.f)) <= EPS)
			uv_pos = (float2)(((-hitpos.x + 1.f) * 0.5f),
			((hitpos.z + 1.f) * 0.5f));
		else if (fabs((float)(hitpos.z - 1.f)) <= EPS)
			uv_pos = (float2)(((hitpos.x + 1.f) * 0.5f),
			((hitpos.y + 1.f) * 0.5f));
		else if (fabs((float)(hitpos.z + 1.f)) <= EPS)
			uv_pos = (float2)(((-hitpos.x + 1.f) * 0.5f),
			((hitpos.y + 1.f) * 0.5f));
	}
	else if (obj->uv_projection == cylindrical)
		uv_pos = (float2)((0.5f + acos(hitpos.x) * (0.5f * INV_PI)),
		((hitpos.z + 1.f) * 0.5f));
	return (uv_pos);
}

static float		rt_cl_get_height_map
(
					__constant	t_object *	obj,
								float2		uv_pos,
								float2		uv_scale
)
{
	float	height_map;

	height_map = 0.f;
	if (obj->pattern == solid)
		height_map = 1.f;
	else if (obj->pattern == horizontal_wave)
		height_map = (sin((float)(uv_pos.x * 2.f * TAU * uv_scale.x)) + 1.f) * 0.5f;
	else if (obj->pattern == vertical_wave)
		height_map = (cos((float)(uv_pos.y * 2.f * TAU * uv_scale.y)) + 1.f) * 0.5f;
	else if (obj->pattern == wave)
		height_map = (cos((float)(uv_pos.y * 2.f * TAU * uv_scale.x)) + 1.f) * 0.5f
		* (sin((float)(uv_pos.x * 2.f * TAU * uv_scale.y)) + 1.f) * 0.5f;
	else if (obj->pattern == horizontal_stripe)
	{
		if (fmod((float)(uv_pos.x * uv_scale.x), 1.f) < 0.5f)
			height_map = 1.f;
	}
	else if (obj->pattern == vertical_stripe)
	{
		if (fmod((float)(uv_pos.y * uv_scale.y), 1.f) < 0.5f)
			height_map = 1.f;
	}
	else if (obj->pattern == checkerboard)
	{
		if (fmod((float)(uv_pos.x * uv_scale.x), 1.f) < 0.5f ^ fmod((float)(uv_pos.y * uv_scale.y), 1.f) < 0.5f)
			height_map = 1.f;
	}
	else if (obj->pattern == hue)
	{
		height_map = 1.f;
//		obj->rgb_a = (float3)(texture.uv_pos.x, texture.uv_pos.y, 0.f);
	}
	else if (obj->pattern == noise)
	{
		height_map = rt_cl_perlin_noise_2d(uv_pos * 10, 0.7f, 8, 42);
	}
	else if (obj->pattern == wood)
	{
		height_map = (sin((float)((uv_pos.x + rt_cl_perlin_noise_2d(uv_pos * 10, 0.7f, 8, 42) * 100) * 4 * TAU / 200.f)) + 1) / 2.f;
	}
	return (height_map);
}

static t_texture	rt_cl_get_texture_properties
(
					__constant	t_scene	*	scene,
								uint2 *		random_seeds,
					__constant	t_object *	obj,
								float3		hitpos
)
{
	t_texture	texture;

	texture.uv_scale = (float2)(2.f, 2.f);
	texture.uv_pos = rt_cl_get_uv_position(obj, hitpos);
	texture.height_map = rt_cl_get_height_map(obj, texture.uv_pos, texture.uv_scale);
	texture.rgb = obj->rgb_a * texture.height_map + obj->rgb_b * (1 - texture.height_map);
	return (texture);
}
