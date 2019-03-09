static float3		rt_cl_convert_os_to_uvw
(
					__constant	t_object *	obj,
								float3		hitpos
)
{
	float3	uvw_pos;

	if (obj->uvw_projection == spherical)
	{
		return (
					(float3)
					(
						atan2((float)hitpos.z, (float)hitpos.x) * INV_TAU + 0.5,
						- asin((float)hitpos.y) * INV_PI + 0.5,
						sqrt(dot(hitpos, hitpos))
					)
				);
	}
	else if (obj->uvw_projection == cubic)
		return (
					(float3)
					(
						(hitpos.x + 1.f) * 0.5f,
						(hitpos.z + 1.f) * 0.5f,
						(hitpos.y + 1.f) * 0.5f
					)
				);
	else if (obj->uvw_projection == cylindrical)
	{
		return (
					(float3)
					(
						atan2((float)hitpos.z, (float)hitpos.x) * INV_TAU + 0.5,
						(hitpos.y + 1.f) * 0.5f,
						sqrt(rt_cl_float3_ynull_dot(hitpos, hitpos))
					)
				);
	}
	else 
		return ((float3)(0.f, 0.f, 0.f));
	return (uvw_pos);
}

static float3		rt_cl_convert_uvw_to_os
(
					__constant	t_object *	obj,
								float3		uvw_pos
)
{
	float	theta;
	float	phi;

	float2	sincos_th;
	float2	sincos_phi;

	if (obj->uvw_projection == cubic)
		return (
					(float3)
					(
						uvw_pos.x * 2.f - 1,
						uvw_pos.z * 2.f - 1,
						uvw_pos.y * 2.f - 1
					)
				);
	if (obj->uvw_projection == spherical)
	{
		theta = TAU * uvw_pos.x;
		phi = PI * uvw_pos.y;
		return	(
					(float3)
					(
						- cos((float)theta) * sin((float)phi) * uvw_pos.z,
						cos((float)phi) * uvw_pos.z,
						- sin((float)theta) * sin((float)phi) * uvw_pos.z
					)
				);
	}
	else if (obj->uvw_projection == cylindrical)
	{
		theta = TAU * uvw_pos.x;
		return	(
					(float3)
					(
						- cos((float)theta) * uvw_pos.z,
						uvw_pos.y * 2.f - 1,
						- sin((float)theta) * uvw_pos.z
					)
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

	texel_value = 0.f;
	if (obj->pattern == solid)
		texel_value = 1.f;
	else if (obj->pattern == horizontal_wave)
		rt_cl_get_pattern_horizontal_waves(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == vertical_wave)
		rt_cl_get_pattern_vertical_waves(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == double_wave)
		rt_cl_get_pattern_double_waves(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == horizontal_stripe)
		rt_cl_get_pattern_horizontal_stripes(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == vertical_stripe)
		rt_cl_get_pattern_vertical_stripes(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == checkerboard)
		rt_cl_get_pattern_checkerboard(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == hue)
		texel_value = 1.f;
	else if (obj->pattern == perlin)
		rt_cl_get_pattern_perlin(obj, uvw_pos, uvw_scale, &texel_value);
	else if (obj->pattern == wood)
		rt_cl_get_pattern_wood(obj, uvw_pos, uvw_scale, &texel_value);
	return (texel_value);
}

static float3		rt_cl_get_bump_normal
(
					__constant	t_object *	obj,
								float3		uvw_pos,
								float3		uvw_scale,
								float3		normal,
								bool		is_2d_proj
)
{
	float3		uvw_normal;
	float3		bump_normal;
	float3		uvw_diff;
	float3		vtan1;
	float3		vtan2;
	float		precision;
	float		bumpiness;

	precision = 0.003f;
	bumpiness = 1.f;
	if (is_2d_proj)
	{
		vtan1 = (float3)(2 * precision, 0.f, rt_cl_get_texel_value(obj, (float3)(uvw_pos.x - precision, uvw_pos.y, uvw_pos.z), uvw_scale)
			- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x + precision, uvw_pos.y, uvw_pos.z), uvw_scale));
		vtan2 = (float3)(0.f, 2 * precision, rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y - precision, uvw_pos.z), uvw_scale)
			- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y + precision, uvw_pos.z), uvw_scale));
		vtan1 = rt_cl_convert_uvw_to_os(obj, vtan1);
		vtan2 = rt_cl_convert_uvw_to_os(obj, vtan2);
		bump_normal = normalize(cross(vtan1, vtan2));
	}
	else if (!is_2d_proj)
	{
		uvw_diff = 	(float3)
					(
						(float)(rt_cl_get_texel_value(obj, (float3)(uvw_pos.x - precision, uvw_pos.y, uvw_pos.z), uvw_scale)
						- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x + precision, uvw_pos.y, uvw_pos.z), uvw_scale)),
						(float)(rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y - precision, uvw_pos.z), uvw_scale)
						- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y + precision, uvw_pos.z), uvw_scale)),
						(float)(rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y, uvw_pos.z - precision), uvw_scale)
						- rt_cl_get_texel_value(obj, (float3)(uvw_pos.x, uvw_pos.y, uvw_pos.z + precision), uvw_scale))
					);
		uvw_normal = rt_cl_convert_os_to_uvw(obj, normal);
		uvw_normal = uvw_normal + (uvw_diff * (float3)(bumpiness));
		bump_normal = rt_cl_convert_uvw_to_os(obj, uvw_normal);
//		printf("normal : x : %f, y : %f, z : %f;\nuvw_normal : x : %f, y : %f, z : %f;\nbump_normal : x : %f, y : %f, z : %f;\n", 
//		normal.x, normal.y, normal.z, uvw_normal.x, uvw_normal.y, uvw_normal.z, bump_normal.x, bump_normal.y, bump_normal.z);
		bump_normal = normalize(bump_normal);
	}
	else
		return (normal);
	return (bump_normal);
}

static float3		rt_cl_uint_to_float3
(
					uint		hex
)
{
	return (
				(float3)
				(
					0.f,
					0.f,
					0.f
				)
			);
}
//TODO Add UI for texture
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
	bool		is_bump;
	bool		is_image_texture;

	is_bump = false;
	is_2d_proj = false;
	is_image_texture = true;
	texture.uvw_offset = (float3)(0.f, 0.f, 0.f);
	texture.uvw_scale = (float3)(1.f, 1.f, 1.f);
	texture.uvw_pos = rt_cl_convert_os_to_uvw(obj, hitpos);
	texture.uvw_pos = fmod((float3)(texture.uvw_pos + texture.uvw_offset), 1.f);
	//TODO add conditional for 2d texturing vs 3d texturing
/*	if (is_image_texture)
	{
		texture.rgb = obj->rgb_texture[0];
	}
	else
	{
*/
		texture.texel_value = rt_cl_get_texel_value(obj, texture.uvw_pos, texture.uvw_scale);
		texture.rgb = obj->rgb_a * texture.texel_value + obj->rgb_b * (1 - texture.texel_value);
//	}
	if (is_bump && is_2d_proj)
		texture.uvw_pos.z = texture.texel_value;
	else if (is_bump)
		texture.bump_normal = rt_cl_get_bump_normal(obj, texture.uvw_pos, texture.uvw_scale, normal, is_2d_proj);
	else
		texture.bump_normal = normal;
	return (texture);
}
