static float		rt_cl_rawnoise
(
					uint	n
)
{
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) * 9.3132257e-10f);/// 1073741824.0f);
}

static float		rt_cl_noise_1d
(
					uint	x,
					uint	octave,
					uint	seed
)
{
	return (rt_cl_rawnoise(x * 1619 + octave * 3463 + seed * 13397));
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

static float		rt_cl_cos_interpolate
(
					float2	range,
					float	x
)
{
	float	f;

	f = (1.f - cos((float)(x * PI))) * 0.5f;
	return (range.x * (1.f - f) + range.y * f);
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
	float2	v;

	int_x = (uint)x;
	frac = x - int_x;
	v.x = rt_cl_noise_1d(x, octave, seed);
	v.y = rt_cl_noise_1d(x + 1, octave, seed);
	return (rt_cl_cos_interpolate((float2)(v.x, v.y), frac));
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
	float4	v;
	float2	level;

	int_pos = (uint2)((uint)pos.x, (uint)pos.y);
	frac = pos - (float2)((float)int_pos.x, (float)int_pos.y);
	v.x = rt_cl_noise_2d(int_pos, octave, seed);
	v.y = rt_cl_noise_2d((uint2)(int_pos.x + 1, int_pos.y), octave, seed);
	v.z = rt_cl_noise_2d((uint2)(int_pos.x, int_pos.y + 1), octave, seed);
	v.w = rt_cl_noise_2d((uint2)(int_pos.x + 1, int_pos.y + 1), octave, seed);
	level.x = rt_cl_cos_interpolate((float2)(v.x, v.y), frac.x);
	level.y = rt_cl_cos_interpolate((float2)(v.z, v.w), frac.x);
	return (rt_cl_cos_interpolate(level, frac.y));
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
	float8	v;
	float4	level;
	float2	high_level;

	int_pos = (uint3)((uint)pos.x, (uint)pos.y, (uint)pos.z);
	frac = pos - (float3)((float)int_pos.x, (float)int_pos.y, (float)int_pos.z);
	v.s0 = rt_cl_noise_3d(int_pos, octave, seed);
	v.s1 = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y, int_pos.z), octave, seed);
	v.s2 = rt_cl_noise_3d((uint3)(int_pos.x, int_pos.y + 1, int_pos.z), octave, seed);
	v.s3 = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y + 1, int_pos.z), octave, seed);
	v.s4 = rt_cl_noise_3d((uint3)(int_pos.x, int_pos.y, int_pos.z + 1), octave, seed);
	v.s5 = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y, int_pos.z + 1), octave, seed);
	v.s6 = rt_cl_noise_3d((uint3)(int_pos.x, int_pos.y + 1, int_pos.z + 1), octave, seed);
	v.s7 = rt_cl_noise_3d((uint3)(int_pos.x + 1, int_pos.y + 1, int_pos.z + 1), octave, seed);
	level.s0 = rt_cl_cos_interpolate(v.s01, frac.x);
	level.s1 = rt_cl_cos_interpolate(v.s23, frac.x);
	level.s2 = rt_cl_cos_interpolate(v.s45, frac.x);
	level.s3 = rt_cl_cos_interpolate(v.s67, frac.x);
	high_level.s0 = rt_cl_cos_interpolate(level.s01, frac.y);
	high_level.s1 = rt_cl_cos_interpolate(level.s23, frac.y);
	return (rt_cl_cos_interpolate(high_level, frac.z));
}

static float		rt_cl_perlin_noise_1d
(
					float	x,
					float	persistence,
					uint	octaves,
					uint	seed
)
{
	float	total = 0.0f;
	float	frequency = 1.0f;
	float	amplitude = 1.0f;

	for (uint i = 0; i < octaves; i++)
	{
		total += rt_cl_smooth_noise_1d(x * frequency, i, seed) * amplitude;
		frequency *= 0.5f;
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
	float	total = 0.0f;
	float	frequency = 1.0f;
	float	amplitude = 1.0f;

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
	float	total = 0.0f;
	float	frequency = 1.0f;
	float	amplitude = 1.0f;

	for (uint i = 0; i < octaves; i++)
	{
		total += rt_cl_smooth_noise_3d(pos * (float3)frequency, i, seed) * amplitude;
		frequency *= 0.5f;
		amplitude *= persistence;
	}
	return (total);
}