static float3		rt_cl_convert_os_to_uvw
(
					__constant	t_object *	obj,
								float3		hitpos
)
{
	float3	uvw_pos;

	if (obj->uvw_projection == spherical)
	{
		float	theta = acos(hitpos.y / uvw_pos.z);
		float	phi = atan2(hitpos.z, hitpos.x);

		uvw_pos.x = phi * INV_TAU;
		uvw_pos.y = theta * INV_PI;
		uvw_pos.z = sqrt((float)dot(hitpos, hitpos));
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
		float	phi = atan2(hitpos.z, hitpos.x);

		uvw_pos.x = phi * INV_TAU;
		uvw_pos.y = (hitpos.y + 1.f) * 0.5f;
		uvw_pos.z = sqrt((float)rt_cl_float3_ynull_dot(hitpos, hitpos));
	}
	else 
		return ((float3)(0.f, 0.f, 0.f));
	return (uvw_pos);
}

//TODO Manage offset here
static float3		rt_cl_convert_uvw_to_os
(
					__constant	t_object *	obj,
								float3		uvw_pos
)
{
	float2	sincos_th;
	float2	sincos_phi;

	if (obj->uvw_projection == cubic)
		return ((uvw_pos.xzy - (float3)(1.f)) * 2.f);
	else if (obj->uvw_projection == spherical)
	{
		sincos_th = (float2)(sin((float)(uvw_pos.y * PI)), cos((float)(uvw_pos.y * PI)));
		sincos_phi = (float2)(sin((float)(uvw_pos.x * TAU)), cos((float)(uvw_pos.x * TAU)));

		return	(
					(float3)(uvw_pos.z) *
						(float3)
						(
							sincos_th.x * sincos_phi.y,
							sincos_th.y,
							sincos_th.x * sincos_phi.x
						)
				);
	}
	else if (obj->uvw_projection == cylindrical)
	{
		sincos_phi = (float2)(sin((float)(uvw_pos.x * TAU)), cos((float)(uvw_pos.x * TAU)));

		return	(
					(float3)
					(
						uvw_pos.z * sincos_phi.y,
						(uvw_pos.y - 1.f) * 2.f,
						uvw_pos.z * sincos_phi.x
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
	float3		bump_normal;
	float3		vtan1;
	float3		vtan2;
	float		precision;

	precision = 0.001f;
	bump_normal = (float3)(0.f, 0.f, 0.f);
	//if () //TODO add conditional to NOT use precalced w = f(u,v) for 3d texture projections
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
	//TODO find jacobienne
	else if (obj->uvw_projection == cubic)
		bump_normal = normal;
	else if (obj->uvw_projection == spherical)
		bump_normal = normal;
	else
		return (normal);
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
	texture.uvw_offset = (float3)(0.f, 0.f, 0.f);
	texture.uvw_scale = (float3)(1.f, 1.f, 1.f);
	texture.uvw_pos = rt_cl_convert_os_to_uvw(obj, hitpos);
	texture.uvw_pos = fmod((float3)(texture.uvw_pos + texture.uvw_offset), 1.f);
	texture.texel_value = rt_cl_get_texel_value(obj, texture.uvw_pos, texture.uvw_scale);
	//TODO add conditional for 2d texturing vs 3d texturing
	if (is_2d_proj)
		texture.uvw_pos.z = texture.texel_value;
	texture.bump_normal = rt_cl_get_bump_normal(obj, texture.uvw_pos, texture.uvw_scale, normal, is_2d_proj);
	texture.rgb = obj->rgb_a * texture.texel_value + obj->rgb_b * (1 - texture.texel_value);
	return (texture);
}
