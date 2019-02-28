static t_color	rt_cl_get_color_properties
(
				__constant	t_scene	*	scene,
							t_object	obj,
							float3		hitpos,
							float3		normal
)
{
	t_color	color;

//	obj.texture = horizontal_wave;
	obj.texture = wave;
	if (obj.type == sphere)
	{
		color.uv_pos.x = (1 + atan2((float)(normal.z), (float)(normal.x)) * INV_PI) * 0.5; 
		color.uv_pos.y = acos((float)(normal.y)) * INV_PI;
	}	
	if (obj.texture == horizontal_wave)
		color.uv_map = (sin((float)(color.uv_pos.x * 2 * TAU * 4)) + 1) * 0.5;
	else if (obj.texture == vertical_wave)
		color.uv_map = (cos((float)(color.uv_pos.y * 2 * TAU * 4)) + 1) * 0.5;
	else if (obj.texture == wave)
		color.uv_map = (cos((float)(color.uv_pos.y * 2 * TAU * 4)) + 1) * 0.5
		* (sin((float)(color.uv_pos.x * 2 * TAU * 8)) + 1) * 0.5;
	else if (obj.texture == hue)
	{
		color.uv_map = 1;
		obj.rgb = (float3)(color.uv_pos.x, color.uv_pos.y, 0);
	}
	color.rgb = color.uv_map * obj.rgb;
	return (color);
}
