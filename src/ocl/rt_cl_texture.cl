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

static t_texture	rt_cl_get_texture_properties
(
					__constant	t_scene	*	scene,
								uint2 *		random_seeds,
								t_object	obj,
								float3		hitpos
)
{
	t_texture	texture;

	texture.light_map = 0.f;
	texture.uv_scale = (float2)(2.f, 2.f);
//	obj.pattern = solid;
//	obj.pattern = horizontal_wave;
//	obj.pattern = vertical_wave;
//	obj.pattern = wave;
//	obj.pattern = horizontal_stripe;
//	obj.pattern = vertical_stripe;
//	obj.pattern = checkerboard;
//	obj.pattern = hue;
//	obj.pattern = noise;
	if (obj.uv_projection == spherical)
	{
		texture.uv_pos.x = 0.5f + atan2((float)(hitpos.z), (float)(hitpos.x)) * (0.5f * INV_PI);
		texture.uv_pos.y = 0.5f - asin((float)(hitpos.y)) * INV_PI;
	}
	else if (obj.uv_projection == cubic)
	{
		if (fabs((float)(hitpos.x - 1.f)) <= EPS)
		{
			texture.uv_pos.x = (hitpos.z + 1.f) * 0.5f;
			texture.uv_pos.y = (hitpos.y + 1.f) * 0.5f;
		}
		else if (fabs((float)(hitpos.x + 1.f)) <= EPS)
		{
			texture.uv_pos.x = (-hitpos.z + 1.f) * 0.5f;
			texture.uv_pos.y = (hitpos.y + 1.f) * 0.5f;
		}
		else if (fabs((float)(hitpos.y - 1.f)) <= EPS)
		{
			texture.uv_pos.x = (hitpos.x + 1.f) * 0.5f;
			texture.uv_pos.y = (hitpos.z + 1.f) * 0.5f;
		}
		else if (fabs((float)(hitpos.y + 1.f)) <= EPS)
		{
			texture.uv_pos.x = (-hitpos.x + 1.f) * 0.5f;
			texture.uv_pos.y = (hitpos.z + 1.f) * 0.5f;
		}
		else if (fabs((float)(hitpos.z - 1.f)) <= EPS)
		{
			texture.uv_pos.x = (hitpos.x + 1.f) * 0.5f;
			texture.uv_pos.y = (hitpos.y + 1.f) * 0.5f;
		}
		else
		{
			texture.uv_pos.x = (-hitpos.x + 1.f) * 0.5f;
			texture.uv_pos.y = (hitpos.y + 1.f) * 0.5f;
		}
	}
	else if (obj.uv_projection == cylindrical)
	{
		texture.uv_pos.x = acos(hitpos.x) * (0.5f * INV_PI);
		texture.uv_pos.y = (hitpos.z + 1.f) * 0.5f;
	}
	else
	{
			texture.uv_pos.x = 0.5f + atan2((float)(hitpos.z), (float)(hitpos.x)) * (0.5f * INV_PI);
		texture.uv_pos.y = 0.5f - asin((float)(hitpos.y)) * INV_PI;
	}
	if (obj.pattern == solid)
		texture.light_map = 1.f;
	else if (obj.pattern == horizontal_wave)
		texture.light_map = (sin((float)(texture.uv_pos.x * 2.f * TAU * texture.uv_scale.x)) + 1.f) * 0.5f;
	else if (obj.pattern == vertical_wave)
		texture.light_map = (cos((float)(texture.uv_pos.y * 2.f * TAU * texture.uv_scale.y)) + 1.f) * 0.5f;
	else if (obj.pattern == wave)
		texture.light_map = (cos((float)(texture.uv_pos.y * 2.f * TAU * texture.uv_scale.x)) + 1.f) * 0.5f
		* (sin((float)(texture.uv_pos.x * 2.f * TAU * texture.uv_scale.y)) + 1.f) * 0.5f;
	else if (obj.pattern == horizontal_stripe)
	{
		if (fmod((float)(texture.uv_pos.x * texture.uv_scale.x), 1.f) < 0.5f)
			texture.light_map = 1.f;
	}
	else if (obj.pattern == vertical_stripe)
	{
		if (fmod((float)(texture.uv_pos.y * texture.uv_scale.y), 1.f) < 0.5f)
			texture.light_map = 1.f;
	}
	else if (obj.pattern == checkerboard)
	{
		if (fmod((float)(texture.uv_pos.x * texture.uv_scale.x), 1.f) < 0.5f ^ fmod((float)(texture.uv_pos.y * texture.uv_scale.y), 1.f) < 0.5f)
			texture.light_map = 1.f;
	}
	else if (obj.pattern == hue)
	{
		texture.light_map = 1.f;
		obj.rgb_a = (float3)(texture.uv_pos.x, texture.uv_pos.y, 0.f);
	}
	else if (obj.pattern == noise)
	{
		texture.light_map = rt_cl_perlin_noise_2d(texture.uv_pos * 10, 0.7f, 8, 42);
	}
	else if (obj.pattern == wood)
	{
		texture.light_map = (sin((float)((texture.uv_pos.x + rt_cl_perlin_noise_2d(texture.uv_pos * 10, 0.7f, 8, 42) * 100) * 4 * TAU / 200.f)) + 1) / 2.f;
	}
	texture.rgb = obj.rgb_a * texture.light_map + obj.rgb_b * (1 - texture.light_map);
	return (texture);
}
