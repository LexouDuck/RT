static t_color	rt_cl_get_color_properties
(
				__constant	t_scene	*	scene,
							t_object	obj,
							float3		hitpos,
							float3		normal
)
{
	t_color	color;

	color.light_map = 0.f;
	color.uv_scale = (float2)(8.f, 4.f);
	obj.texture = none;
//	obj.texture = horizontal_wave;
//	obj.texture = vertical_wave;
//	obj.texture = wave;
//	obj.texture = horizontal_stripe;
//	obj.texture = vertical_stripe;
//	obj.texture = checkerboard;	
//	obj.texture = hue;
	if (obj.type == sphere)
	{
		color.uv_pos.x = (1 + atan2((float)(normal.z), (float)(normal.x)) * INV_PI) * 0.5; 
		color.uv_pos.y = acos((float)(normal.y)) * INV_PI;
	}
	if (obj.texture == none)
		color.light_map = 1;
	else if (obj.texture == horizontal_wave)
		color.light_map = (sin((float)(color.uv_pos.x * 2 * TAU * color.uv_scale.x)) + 1) * 0.5;
	else if (obj.texture == vertical_wave)
		color.light_map = (cos((float)(color.uv_pos.y * 2 * TAU * color.uv_scale.y)) + 1) * 0.5;
	else if (obj.texture == wave)
		color.light_map = (cos((float)(color.uv_pos.y * 2 * TAU * color.uv_scale.x)) + 1) * 0.5
		* (sin((float)(color.uv_pos.x * 2 * TAU * color.uv_scale.y)) + 1) * 0.5;
	else if (obj.texture == horizontal_stripe)
	{
		if (fmod((float)(color.uv_pos.x * color.uv_scale.x), 1) < 0.5)
			color.light_map = 1;
	}
	else if (obj.texture == vertical_stripe)
	{
		if (fmod((float)(color.uv_pos.y * color.uv_scale.y), 1) < 0.5)
			color.light_map = 1;
	}
	else if (obj.texture == checkerboard)
	{
		if (fmod((float)(color.uv_pos.x * color.uv_scale.x), 1) < 0.5 ^ fmod((float)(color.uv_pos.y * color.uv_scale.y), 1) < 0.5)
			color.light_map = 1;
	}
	else if (obj.texture == hue)
	{
		color.light_map = 1;
		obj.rgb = (float3)(color.uv_pos.x, color.uv_pos.y, 0);
	}
	color.rgb = color.light_map * obj.rgb;
	return (color);
}
