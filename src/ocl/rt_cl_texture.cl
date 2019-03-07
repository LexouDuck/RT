static float3		rt_cl_convert_os_to_uvw
(
					__constant	t_object *	obj,
								float3		hitpos
)
{
	float3	uvw_pos;

	if (obj->uvw_projection == spherical)
	{
		uvw_pos.z = sqrt((float)rt_cl_float3_ynull_dot(hitpos, hitpos));
		uvw_pos.y = atan2(hitpos.z, hitpos.x) * INV_TAU;
		uvw_pos.x = acos(hitpos.y / uvw_pos.z) * INV_PI;
	}
	else if (obj->uvw_projection == cubic)
		uvw_pos = hitpos.xzy;
	else if (obj->uvw_projection == cylindrical)
	{
		uvw_pos.x = sqrt((float)rt_cl_float3_ynull_dot(hitpos, hitpos));
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
	float2	sin_pos;
	float2	cos_pos;

	sin_pos = sincos((float2)(uvw_pos.xy), &cos_pos);
	if (obj->uvw_projection == cubic)
		return (uvw_pos.xzy);
	else if (obj->uvw_projection == spherical)
	{
		return	( (float3)(uvw_pos.z) *
					(float3)(	sin_pos.x * cos_pos.y,
								cos_pos.x,
								sin_pos.x * sin_pos.y)
				);
	}
	else if (obj->uvw_projection == cylindrical)
	{
		return ((float3)(	uvw_pos.x * cos_pos.y,
							uvw_pos.z,
							uvw_pos.x * sin_pos.y)
				);
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
	float3	uvw_offset = rt_cl_convert_os_to_uvw(obj, obj->bbox_os.vi);

	texel_value = 0.f;
	if (obj->pattern == solid)
		texel_value = 1.f;
	else if (obj->pattern == horizontal_wave)
		texel_value = (sin((float)(uvw_pos.x * TWOTAU * uvw_scale.x)) + 1.f) * 0.5f;
	else if (obj->pattern == vertical_wave)
		texel_value = (cos((float)(uvw_pos.y * TWOTAU * uvw_scale.y)) + 1.f) * 0.5f;
	else if (obj->pattern == wave)
		texel_value = (cos((float)(uvw_pos.y * TWOTAU * uvw_scale.x)) + 1.f)
					* (sin((float)(uvw_pos.x * TWOTAU * uvw_scale.y)) + 1.f) * 0.25f;
	else if (obj->pattern == horizontal_stripe
			&& fmod((float)((uvw_pos.x - uvw_offset.x) * uvw_scale.x), 1.f) < 0.5f)
		texel_value = 1.f;
	else if (obj->pattern == vertical_stripe
			&& fmod((float)((uvw_pos.y - uvw_offset.y) * uvw_scale.y), 1.f) < 0.5f)
		texel_value = 1.f;
	else if (obj->pattern == checkerboard
			&& 	fmod((float)((uvw_pos.x - uvw_offset.x) * uvw_scale.x), 1.f) < 0.5f
				^ fmod((float)((uvw_pos.y - uvw_offset.y) * uvw_scale.y), 1.f) < 0.5f)
		texel_value = 1.f;
	else if (obj->pattern == hue)
		texel_value = 1.f;
//		obj->rgb_a = (float3)(texture.uv_pos.x, texture.uv_pos.y, 0.f);
	else if (obj->pattern == noise)
		texel_value = rt_cl_perlin_noise_3d(uvw_pos * 10, 0.7f, 8, 42);
	else if (obj->pattern == wood)
		texel_value = (sin((float)((uvw_pos.x + rt_cl_perlin_noise_3d(uvw_pos * 10, 0.7f, 8, 42) * 100) * TAU * 0.02f)) + 1) * 0.5f;
	return (texel_value);
}

static float3		rt_cl_get_bump_normal
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float3		normal,
//								float		texel_value,
								bool		is_2d_proj
)
{
//	float		length_du;
//	float		length_dv;
	float3		bump_normal;
	float3		vtan1;
	float3		vtan2;
//	float16		lin_mat;
	float		precision;

	precision = 0.001f;
	bump_normal = normal;//(float3)(0.f, 0.f, 0.f);
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
	else if (obj->uvw_projection == cubic)
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
	bool		is_2d_proj;

	is_2d_proj = false;
	texture.uvw_scale = fabs(obj->bbox_os.vi - obj->bbox_os.vf);
	texture.uvw_scale = rt_cl_convert_os_to_uvw(obj, texture.uvw_scale);
//	texture.uvw_scale.yz = texture.uvw_scale.zy;
	texture.uvw_pos = rt_cl_convert_os_to_uvw(obj, hitpos);
	texture.texel_value = rt_cl_get_texel_value(obj, texture.uvw_pos, texture.uvw_scale);
	if (is_2d_proj) //TODO add conditional for 2d texturing vs 3d texturing
		texture.uvw_pos.z = texture.texel_value;
	texture.bump_normal = rt_cl_get_bump_normal(obj, texture.uvw_pos, texture.uvw_scale, normal, /*texture.texel_value,*/ is_2d_proj);
	texture.rgb = obj->rgb_a * texture.texel_value + obj->rgb_b * (1 - texture.texel_value);
	return (texture);
}
