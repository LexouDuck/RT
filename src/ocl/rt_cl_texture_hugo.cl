static float		rt_cl_rawnoise
(
					uint	n
)
{
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

static float		rt_cl_noise_1d
(
					uint	x,
					uint	octave,
					uint	seed
)
{
	return (rt_cl_rawnoise(x * 1619 + octave * 3463 + seed 13397));
}

static float		rt_cl_noise_2d
(
					uint2	pos,
					uint	octave,
					uint	seed
)
{
    return (rt_cl_rawnoise(pos.x * 1619 + pos.y * 31337 + octave * 3463 + seed * 13397));
}

static float		rt_cl_noise_3d
(
					uint3	pos,
					uint	octave,
					uint	seed
)
{
	return (rt_cl_rawnoise(pos.x * 1919 + pos.y * 31337 + pos.z * 7669 + octave * 3463 + seed * 13397));
}

static float		rt_cl_interpolate
(
					float2	range,
					float	x
)
{
	float	f;

	f = (1 - cos((float)(x * PI))) * 0.5f;
	return (range.x * (1 - f) + range.y * f);
}

static float		rt_cl_smooth_noise_1d
(
					float	x,
					uint	octave,
					uint	seed
)
{
	uint	int_x;
	float	frac;
	float	v[2];

	int_x = (int)x;
	frac = x - int_x;
	v[0] = rt_cl_noise_1d(x, octave, seed);
	v[1] = rt_cl_noise_1d(x + 1, octave, seed);
	return (rt_cl_interpolate((float2)(v[0], v[1]), frac));
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
	float	v[4];
	float2	uv_pos;
	float	level[2];

	int_pos = (int)pos;
	frac = pos - int_pos;
	v[0] = rt_cl_noise_2d(int_pos, octave, seed);
	v[1] = rt_cl_noise_2d((uint2)(int_pos.x + 1, int_pos.y), octave, seed);
	v[2] = rt_cl_noise_2d((uint2)(int_pos.x, int_pos.y + 1), octave, seed);
	v[3] = rt_cl_noise_2d((uint2)(int_pos.x + 1, int_pos.y + 1), octave, seed);
	level[0] = rt_cl_interpolate((float2)(v[0], v[1]), frac.x);
	level[1] = rt_cl_interpolate((float2)(v[2], v[3]), frac.x);
	return (rt_cl_interpolate((float2)(level[0], level[1]), frac.y));
}

static float		rt_cl_smooth_noise_3d
(
					float3	pos,
					uint	octave,
					uint	seed
)
{
	uint3	int_pos;
	float3	frac;
	float	v[8];
	float2	uv_pos;
	float	level[6];
	float	high_level[2];

	int_pos = (int)pos;
	frac = pos - int_pos;
	v[0] = rt_cl_noise_3d(int_pos, octave, seed);
	v[1] = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y, int_pos.z), octave, seed);
	v[2] = rt_cl_noise_3d((uint3)(int_pos.x, int_pos.y + 1, int_pos.z), octave, seed);
	v[3] = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y + 1, int_pos.z), octave, seed);
	v[4] = rt_cl_noise_3d((uint3)(int_pos.x, int_pos.y, int_pos.z + 1), octave, seed);
	v[5] = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y, int_pos.z + 1), octave, seed);
	v[6] = rt_cl_noise_3d((uint3)(int_pos.x, int_pos.y + 1, int_pos.z + 1), octave, seed);
	v[7] = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y + 1, int_pos.z + 1), octave, seed);
	level[0] = rt_cl_interpolate((float2)(v[0], v[1]), frac.x);
	level[1] = rt_cl_interpolate((float2)(v[2], v[3]), frac.x);
	level[2] = rt_cl_interpolate((float2)(v[4], v[5]), frac.x);
	level[3] = rt_cl_interpolate((float2)(v[6], v[7]), frac.x);
	high_level[0] = rt_cl_interpolate((float2)(level[0], level[1]), frac.y);
	high_level[1] = rt_cl_interpolate((float2)(level[2], level[3]), frac.y);
	return (rt_cl_interpolate((float2)(high_level[0], high_level[1]), frac.z));
}

static float		rt_cl_perlin_noise_1d
(
					float	x,
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
		total += rt_cl_smooth_noise_1d(x * frequency, i, seed) * amplitude;
		frequency *= 0.5;
		amplitude *= persistence;
	}
	return (total);
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
		total += rt_cl_smooth_noise_2d(pos * (float2)frequency, i, seed) * amplitude;
		frequency *= 0.5f;
		amplitude *= persistence;
	}
	return (total);
}

static float		rt_cl_perlin_noise_3d
(
					float3	pos,
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
		total += rt_cl_smooth_noise_3d(pos * (float3)frequency, i, seed) * amplitude;
		frequency *= 0.5f;
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
