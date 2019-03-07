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

	int_x = (uint)x;
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

	int_pos = (uint2)((uint)pos.x, (uint)pos.y);
	frac = pos - (float2)((float)int_pos.x, (float)int_pos.y);
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

	int_pos = (uint3)((uint)pos.x, (uint)pos.y, (uint)pos.z);
	frac = pos - (float3)((float)pos.x, (float)pos.y, (float)pos.z);
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

#if 0
static void			rt_cl_convert_cube_uv_to_hitpos
(
					float2		uv_pos,
					float3 *	hitpos,
					uint		cube_index
)
{
	// convert range 0 to 1 to -1 to 1
	float uc;
	float vc;

	uc = 2.0f * uv_pos.x - 1.0f;
	vc = 2.0f * uv_pos.y - 1.0f;
	switch (cube_index)
	{
		//TODO *hitpos = (float3)...; break;
		// Positive x
		case 0: hitpos->x = 1.0f;	hitpos->y = vc;		hitpos->z = -uc;	break;
		// Negative x
		case 1: hitpos->x = -1.0f;	hitpos->y = vc;		hitpos->z = uc;		break;
		// Positive y
		case 2: hitpos->x = uc;		hitpos->y = 1.0f;	hitpos->z = -vc;	break;
		// Negative y
		case 3: hitpos->x = uc;		hitpos->y = -1.0f;	hitpos->z = vc;		break;
		// Positive z
		case 4: hitpos->x = uc;		hitpos->y = vc;		hitpos->z = 1.0f;	break;
		// Negative z
		case 5: hitpos->x = -uc;	hitpos->y = vc;		hitpos->z = -1.0f; break;
	}
}

//TODO replace with uvw texture space handling
static void			rt_cl_convert_hitpos_to_cube_uv
(
					float3		hitpos,
					float2 *	uv_pos,
					uint *		cube_index	
)
{
	float3	abs_hitpos;
	bool	is_x_positive;
	bool	is_y_positive;
	bool	is_z_positive;
	float	max_axis;
	float	uc;
	float	vc;

	abs_hitpos = (float3)(fabs(hitpos.x), fabs(hitpos.y), fabs(hitpos.z));
	is_x_positive = hitpos.x > 0 ? true : false;
	is_y_positive = hitpos.y > 0 ? true : false;
	is_z_positive = hitpos.z > 0 ? true : false;
	// Positive x, u (0 to 1) goes from +z to -z, v (0 to 1) goes from -y to +y
	if (is_x_positive && abs_hitpos.x >= abs_hitpos.y && abs_hitpos.x >= abs_hitpos.z)
	{
		max_axis = abs_hitpos.x;
		uc = -hitpos.z;
 		vc = hitpos.y;
		*cube_index = 0;
	}
	// Negative x, u (0 to 1) goes from -z to +z, v (0 to 1) goes from -y to +y
	if (!is_x_positive && abs_hitpos.x >= abs_hitpos.y && abs_hitpos.x >= abs_hitpos.z)
	{
		max_axis = abs_hitpos.x;
		uc = hitpos.z;
		vc = hitpos.y;
		*cube_index = 1;
	}
	// Positive y, u (0 to 1) goes from -x to +x, v (0 to 1) goes from +z to -z
	if (is_y_positive && abs_hitpos.y >= abs_hitpos.x && abs_hitpos.y >= abs_hitpos.z)
	{
		max_axis = abs_hitpos.y;
		uc = hitpos.x;
		vc = -hitpos.z;
		*cube_index = 2;
	}
	// Negative y, u (0 to 1) goes from -x to +x, v (0 to 1) goes from -z to +z
	if (!is_y_positive && abs_hitpos.y >= abs_hitpos.x && abs_hitpos.y >= abs_hitpos.z)
	{
		max_axis = abs_hitpos.y;
		uc = hitpos.x;
		vc = hitpos.z;
		*cube_index = 3;
	}
	// Positive z, u (0 to 1) goes from -x to +x, v (0 to 1) goes from -y to +y
	if (is_z_positive && abs_hitpos.z >= abs_hitpos.x && abs_hitpos.z >= abs_hitpos.y)
	{
		max_axis = abs_hitpos.z;
		uc = hitpos.x;
		vc = hitpos.y;
		*cube_index = 4;
	}
	// Negative z, u (0 to 1) goes from +x to -x, v (0 to 1) goes from -y to +y
	if (!is_z_positive && abs_hitpos.z >= abs_hitpos.x && abs_hitpos.z >= abs_hitpos.y)
	{
		max_axis = abs_hitpos.z;
		uc = -hitpos.x;
		vc = hitpos.y;
		*cube_index = 5;
	}
	// Convert range from -1 to 1 to 0 to 1
	uv_pos->x = 0.5f * (uc / max_axis + 1.0f);
	uv_pos->y = 0.5f * (vc / max_axis + 1.0f);
}
#endif

static float3		rt_cl_convert_os_to_uvw
(
					__constant	t_object *	obj,
								float3		hitpos
)
{
	float3	uvw_pos;

	if (obj->uvw_projection == spherical)
	{
		uvw_pos.z = sqrt((float)(pow(hitpos.x, 2) + pow(hitpos.z, 2)));
		uvw_pos.y = atan2(hitpos.z, hitpos.x) * INV_TAU;
		uvw_pos.x = acos(hitpos.y / uvw_pos.z) * INV_PI;
	}
	else if (obj->uvw_projection == cubic)
		uvw_pos = hitpos.xzy;
	else if (obj->uvw_projection == cylindrical)
	{
		uvw_pos.x = sqrt((float)(pow(hitpos.x, 2) + pow(hitpos.z, 2)));
		uvw_pos.y = atan2(hitpos.z, hitpos.x);
		uvw_pos.z = hitpos.y;
	}
	return (uvw_pos);
}

static float3		rt_cl_convert_uvw_to_os
(
					__constant	t_object *	obj,
								float3		uvw_pos
)
{
	if (obj->uvw_projection == cubic)
		return (uvw_pos.xzy);
	else if (obj->uvw_projection == spherical)
	{
		//TODO minimize call to sin and cos with two calls to sincos
		return	( (float3)(uvw_pos.z) *
					(float3)(	sin(uvw_pos.x) * cos(uvw_pos.y),
								cos(uvw_pos.x),
								sin(uvw_pos.x) * sin(uvw_pos.y))
				);
	}
	else if (obj->uvw_projection == cylindrical)
	{
		return ((float3)(	uvw_pos.x * cos(uvw_pos.y),
							uvw_pos.z,
							uvw_pos.x * sin(uvw_pos.y)));
	}
	return (uvw_pos.xzy);
}

static float		rt_cl_get_texel_value
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale
)
{
	float	texel_value;

	texel_value = 0.f;
	if (obj->pattern == solid)
	{
		texel_value = 1.f;
	}
	else if (obj->pattern == horizontal_wave)
	{
		texel_value = (sin((float)(uvw_pos.x * 2.f * TAU * uvw_scale.x)) + 1.f) * 0.5f;
	}
	else if (obj->pattern == vertical_wave)
	{
		texel_value = (cos((float)(uvw_pos.y * 2.f * TAU * uvw_scale.y)) + 1.f) * 0.5f;
	}
	else if (obj->pattern == wave)
	{
		texel_value = (cos((float)(uvw_pos.y * 2.f * TAU * uvw_scale.x)) + 1.f)
					* (sin((float)(uvw_pos.x * 2.f * TAU * uvw_scale.y)) + 1.f) * 0.25f;
	}
	else if (obj->pattern == horizontal_stripe
			&& fmod((float)(uvw_pos.x * uvw_scale.x), 1.f) < 0.5f)
	{
		texel_value = 1.f;
	}
	else if (obj->pattern == vertical_stripe
			&& fmod((float)(uvw_pos.y * uvw_scale.y), 1.f) < 0.5f)
	{
		texel_value = 1.f;
	}
	else if (obj->pattern == checkerboard
			&& fmod((float)(uvw_pos.x * uvw_scale.x), 1.f) < 0.5f ^ fmod((float)(uvw_pos.y * uvw_scale.y), 1.f) < 0.5f)
	{
		texel_value = 1.f;
	}
	else if (obj->pattern == hue)
	{
		texel_value = 1.f;
//		obj->rgb_a = (float3)(texture.uv_pos.x, texture.uv_pos.y, 0.f);
	}
	else if (obj->pattern == noise)
	{
		texel_value = rt_cl_perlin_noise_2d(uvw_pos.xy * 10, 0.7f, 8, 42);
	}
	else if (obj->pattern == wood)
	{
		texel_value = (sin((float)((uvw_pos.x + rt_cl_perlin_noise_2d(uvw_pos.xy * 10, 0.7f, 8, 42) * 100) * TAU * 0.02f)) + 1) * 0.5f;
	}
	return (texel_value);
}


static float3		rt_cl_get_bump_normal
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float3		normal,
								float		texel_value,
								bool		is_2d_proj
)
{
	float		length_du;
	float		length_dv;
	float3		bump_normal;
	float3		vtan1;
	float3		vtan2;
//	float16		lin_mat;
	float		precision;


	is_2d_proj = true;


	precision = 0.001f;
	bump_normal = (float3)(0.f, 0.f, 0.f);
	//if () //TODO add conditional to NOT use precalced w = f(u,v) for 3d texture projections
	if (is_2d_proj)
	{
//		uvw_pos.z = texel_value;
		vtan1 = (float3)(2 * precision, 0.f, rt_cl_get_texel_value(obj, (float3)(uvw_pos.x - precision, uvw_pos.y, uvw_pos.z), uvw_scale)
			- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x + precision, uvw_pos.y, uvw_pos.z), uvw_scale));
		vtan2 = (float3)(0.f, 2 * precision, rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y - precision, uvw_pos.z), uvw_scale)
			- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y + precision, uvw_pos.z), uvw_scale));
		vtan1 = rt_cl_convert_uvw_to_os(obj, vtan1);
		vtan2 = rt_cl_convert_uvw_to_os(obj, vtan2);
		bump_normal = normalize(cross(vtan1, vtan2));
	}
	if (obj->uvw_projection == cubic)
	{
		bump_normal = normal;
	}
	return (bump_normal);
}

static t_texture	rt_cl_get_texture_properties
(
					__constant	t_scene	*	scene,
								uint2 *		random_seeds,
					__constant	t_object *	obj,
								float3		hitpos,
								float3		normal
)
{
	t_texture	texture;
	uint		cube_index;
	bool		is_2d_proj;

	is_2d_proj = true;
	texture.uvw_scale = fabs(obj->bbox_os.vi - obj->bbox_os.vf);
	texture.uvw_scale.yz = texture.uvw_scale.zy;
	texture.uvw_pos = rt_cl_convert_os_to_uvw(obj, hitpos);
	texture.texel_value = rt_cl_get_texel_value(obj, texture.uvw_pos, texture.uvw_scale);
	if (is_2d_proj) //TODO add conditional for 2d texturing vs 3d texturing
		texture.uvw_pos.z = texture.texel_value;
	texture.bump_normal = rt_cl_get_bump_normal(obj, texture.uvw_pos, texture.uvw_scale, normal, is_2d_proj, texture.texel_value);
	texture.rgb = obj->rgb_a * texture.texel_value + obj->rgb_b * (1 - texture.texel_value);
	return (texture);
}
