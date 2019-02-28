static t_ray	rt_cl_get_new_ray_properties
(
				__constant	t_scene	*	scene,
							t_object	obj,
							uint2 *		random_seeds,
							float3		hitpos,
							float3		normal
)
{
	t_ray		new_ray;

	new_ray.pos = rt_cl_apply_homogeneous_matrix(obj.o_to_w, hitpos) + normal * (float3)(EPS);
	new_ray.dir = rt_cl_rand_dir_coshemi(random_seeds, normal);
	new_ray.hit_obj_id = -1;
	new_ray.inter_type = INTER_NONE;
	new_ray.t = scene->render_dist;
/*	new_ray.hit_texture_coordinates.x = (1 + atan2(normal.z, normal.x) / M_PI) * 0.5; 
	new_ray.hit_texture_coordinates.y = acosf(normal.y) / M_PI;*/
	if (obj.type == sphere)
	{
		new_ray.uv_coordinates.x = (1 + atan2((float)(normal.z), (float)(normal.x)) / M_PI) * 0.5; 
		new_ray.uv_coordinates.y = acos((float)(normal.y)) / M_PI;
	}
	if (obj.type == cube)
	{
		if (fabs((float)(new_ray.uv_coordinates.x)) == 1)
		{
			new_ray.uv_coordinates.x = (normal.z + 1) / 2;
			new_ray.uv_coordinates.y = (normal.y + 1) / 2;
		}
		else if (fabs((float)(new_ray.uv_coordinates.y)) == 1)
		{
			new_ray.uv_coordinates.x = (normal.x + 1) / 2;
			new_ray.uv_coordinates.y = (normal.z + 1) / 2;
		}
		else
		{
			new_ray.uv_coordinates.x = (normal.x + 1) / 2;
			new_ray.uv_coordinates.y = (normal.y + 1) / 2;
		}
	}
	return (new_ray);
}