static bool			rt_cl_ray_intersect_bbox
(
					t_ray		ray,
					t_bbox		aabb,
					float		tmin,
					float		tmax,
					float *		tres
)
{
	t_intersection	inter;
	float			tmax_old = tmax;
	//TODO add aabb.vi.x < ray.pos.x < aabb.vf.x: if true for every coordinate, return INTER_INSIDE

	float3	inv_dir = native_recip(ray.dir);
	//get all plane intersections
	float3	ti = (aabb.vi - ray.pos) * inv_dir;
	float3	tf = (aabb.vf - ray.pos) * inv_dir;

	//put all inferior bounds in tinf, and all superior bounds in tsup
	float3	tinf = fmin(ti, tf);
	float3	tsup  = fmax(ti, tf);

	// get biggest inferorior bound tmin and smallest superior bound tmax.
	tmin = fmax(tmin, fmax(tinf.x, fmax(tinf.y, tinf.z)));
	tmax = fmin(tmax, fmin(tsup.x, fmin(tsup.y, tsup.z)));

	//intersection iff no incoherence in all previous checks and tmin = Max(inferior bound) < Min(superior bound) = tmax
	inter = tmin < tmax ? INTER_OUTSIDE : INTER_NONE;
	*tres = inter ? tmin : tmax_old;
	if (*tres == 0.)
	{
		*tres = tmax;
		inter = INTER_INSIDE;
	}
	return (inter);
}

/*
** If BBoxes have a non-empty intersection, you can't use new_t as tmax
** for ray_intersect_bbox.
*/
static t_intersection		rt_cl_trace_ray_to_scene
(
					__constant		t_scene	*	scene,
									t_ray *		ray
)
{
	__constant t_object *		obj;
	t_intersection				bbox_inter;
	t_intersection				prim_inter;
	float						tmax;
	float						new_tbbox;
	float						new_t;
	t_ray						ray_os;
	t_ray						result_ray_os;

	tmax = ray->t;
	prim_inter = INTER_NONE;
	for (uint i = 0; i < scene->object_amount; ++i)
	{
		obj = &(scene->objects[i]);
		bbox_inter = rt_cl_ray_intersect_bbox(*ray, obj->bbox, 0., tmax, &new_tbbox);
		if (bbox_inter)
		{
			if (scene->render_mode == RENDERMODE_BBOX)
			{
				tmax = new_tbbox;
				ray->t = new_tbbox;
				ray->hit_obj_id = i;
				prim_inter = bbox_inter;
			}
			else
			{
				ray_os = *ray;
				ray_os.inter_type = INTER_NONE;
				ray_os.pos = rt_cl_apply_homogeneous_matrix(obj->w_to_o, ray_os.pos);
				ray_os.dir = rt_cl_apply_linear_matrix(obj->w_to_o, ray_os.dir);//DO NOT NORMALIZE: YOU NEED TO KEEP ray.t CONSISTENT

				if (obj->type == sphere)
					ray_os.inter_type = rt_cl_sphere_intersect(&new_t, ray_os);
				else if (obj->type == plane)
					ray_os.inter_type = rt_cl_plane_intersect(&new_t, ray_os);
				else if (obj->type == disk)
					ray_os.inter_type = rt_cl_disk_intersect(&new_t, ray_os);
				else if (obj->type == rectangle)
					ray_os.inter_type = rt_cl_square_intersect(&new_t, ray_os);
				else if (obj->type == cylinder)
					ray_os.inter_type = rt_cl_cylinder_intersect(&new_t, ray_os);
				else if (obj->type == cone)
					ray_os.inter_type = rt_cl_cone_intersect(&new_t, ray_os);
				else if (obj->type == infcylinder)
					ray_os.inter_type = rt_cl_infcylinder_intersect(&new_t, ray_os);
				else if (obj->type == infcone)
					ray_os.inter_type = rt_cl_infcone_intersect(&new_t, ray_os);
				else if (obj->type == cube)
					ray_os.inter_type = rt_cl_cube_intersect(&new_t, ray_os);
				else if (obj->type == paraboloid)
					ray_os.inter_type = rt_cl_paraboloid_intersect(&new_t, ray_os);
				else if (obj->type == hyperboloid)
					ray_os.inter_type = rt_cl_hyperboloid_intersect(&new_t, ray_os);
				else
					ray_os.inter_type = rt_cl_sphere_intersect(&new_t, ray_os);

				if (ray_os.inter_type && new_t > EPS && new_t < ray->t)
				{
					prim_inter = ray_os.inter_type;
					result_ray_os = ray_os;
					result_ray_os.hit_obj_id = i;
					ray->t = new_t;
					result_ray_os.t = new_t;
				}
			}
		}
	}
	if (scene->render_mode != RENDERMODE_BBOX && prim_inter)
		*ray = result_ray_os;
	return (prim_inter);
}

static t_ray			rt_cl_accumulate_lum_and_bounce_ray
(
						__constant	t_scene	*	scene,
									uint2 *		random_seeds,
									t_ray		ray,
									int			sampid,
									int			depth
)
{
	__constant	t_object *	obj = &(scene->objects[ray.hit_obj_id]);
				t_ray		new_ray;
				float3		hitpos;
				float3		normal;
				float3		random_dir;
				float2		uv_mapping;
				float		angle;
				float		pattern;
				float3		texture;


	hitpos = ray.pos + ((float3)ray.t) * ray.dir;
	if (obj->type == sphere)
		normal = rt_cl_sphere_get_normal(hitpos);
	else if (obj->type == plane || obj->type == disk || obj->type == rectangle)
		normal = rt_cl_plane_get_normal(hitpos);
	else if (obj->type == cylinder)
		normal = rt_cl_cylinder_get_normal(hitpos);
	else if (obj->type == infcylinder)
		normal = rt_cl_infcylinder_get_normal(hitpos);
	else if (obj->type == infcone)
		normal = rt_cl_infcone_get_normal(hitpos);
	else if (obj->type == cone)
		normal = rt_cl_cone_get_normal(hitpos);
	else if (obj->type == cube)
		normal = rt_cl_cube_get_normal(hitpos);
	else if (obj->type == paraboloid)
		normal = rt_cl_paraboloid_get_normal(hitpos);
	else if (obj->type == paraboloid)
		normal = rt_cl_hyperboloid_get_normal(hitpos);
	else
		normal = rt_cl_sphere_get_normal(hitpos);
	normal = normalize(rt_cl_apply_linear_matrix(obj->n_to_w, normal)) * ray.inter_type; //sphere formula, normal == hitpos
	new_ray = rt_cl_get_new_ray_properties(scene, *obj, random_seeds, hitpos, normal);

#if 0
	new_ray.complete = obj->material == lightsrc;
	new_ray.lum_mask = ray.lum_mask * obj->rgb;
	new_ray.lum_mask *= (float3)(1. - new_ray.complete) * (float3)(dot(normal, new_ray.dir));
	new_ray.lum_acc = ray.lum_acc + (float3)(new_ray.complete) * new_ray.lum_mask;
#endif
	//TODO echantillonage par importance, séparation éclairage direct et indirect
	if (obj->material == lightsource)
	{
		new_ray.complete = true;
		new_ray.lum_acc = ray.lum_acc + ray.lum_mask * obj->rgb;

		new_ray.lum_mask = ray.lum_mask;
	}
	else if (obj->type == sphere)
	{
		// compute the pattern
	//	angle = (M_PI / 8); 
	//	uv_mapping.x = new_ray.uv_coordinates.x * cos(M_PI / 8) - new_ray.uv_coordinates.y * sin(angle); 
	//	uv_mapping.y = new_ray.uv_coordinates.y * cos(angle) + new_ray.uv_coordinates.x * sin(angle);
		pattern = (sin((float)(new_ray.uv_coordinates.x * TAU * 8)) + 1) * 0.5;
		new_ray.lum_mask = ray.lum_mask * obj->rgb * pattern * (float3)(dot(normal, new_ray.dir));
		new_ray.lum_acc = ray.lum_acc;
	}
/*
	else if (obj->type == cube)
	{
		pattern = (sin(new_ray.uv_coordinates.x * 2 * M_PI * 8) + 1) * 0.5;
		new_ray.lum_mask = ray.lum_mask * obj->rgb * pattern * (float3)(dot(normal, new_ray.dir));
		new_ray.lum_acc = ray.lum_acc;
	}
*/
	else if (obj->material == diffuse)
	{
		new_ray.complete = false;
		new_ray.lum_acc = ray.lum_acc;

		new_ray.dir = rt_cl_rand_dir_coshemi(random_seeds, normal);
		new_ray.lum_mask = ray.lum_mask * obj->rgb * (float3)(dot(normal, new_ray.dir));//cos sampling, defines contribution to ray.lum_acc
	}
	else if (obj->material == glassy)
	{
		new_ray.complete = false;
		new_ray.lum_acc = ray.lum_acc;

		new_ray.lum_mask = (ray.inter_type == INTER_INSIDE) ?
			ray.lum_mask * obj->rgb :
			ray.lum_mask;
		new_ray.dir = rt_cl_get_transmit_or_reflect(random_seeds, ray.dir, ray.inter_type == INTER_INSIDE, normal, 1.25);
		//	Position correction for transmission
		new_ray.pos = mad(-2 * EPS, normal, new_ray.pos);
	}
	else if (obj->material == glossy)
	{
		new_ray.complete = false;
		new_ray.lum_acc = ray.lum_acc;

		float3 reflect = rt_cl_get_reflect(ray.dir, normal);
		new_ray.dir = rt_cl_rand_dir_coslobe(random_seeds, reflect, 7);

		new_ray.lum_mask = ray.lum_mask * obj->rgb * (float3)(dot(normal, reflect));// * obj->rgb;//*dot(new_dir, reflect) ?
	}
	return (new_ray);
}

static t_ray			rt_cl_create_camray
(
					__constant		t_scene	*	scene,
									uint2 *		random_seeds
)
{
	int const			x_id = get_global_id(0);
	int const			y_id = get_global_id(1);
	int const			width = get_global_size(0);
	int const			height = get_global_size(1);
	float16	const		cam_mat44 = scene->camera.c_to_w;
	float const			fov_val = -width / (2 * tan(scene->camera.hrz_fov));
	t_ray				camray;
	float2				seeds;
	float2				box_muller_sample;
	float3				aperture;
	float				focus_distance = 50;

	camray.lum_acc = (float3)(0.);
	camray.lum_mask = (float3)(1.);
	camray.t = scene->render_dist;
	camray.complete = false;
	camray.hit_obj_id = -1;
	camray.inter_type = INTER_NONE;
	if (scene->camera.model == CAMERA_MODEL_PINHOLE)
	{
		camray.pos = (float3)(0., 0., 0.);
		camray.dir = (float3)(x_id - width / 2, y_id - height / 2, fov_val);
	}
	else if (scene->camera.model == CAMERA_MODEL_TMP)
	{
		camray.pos = (float3)(rt_cl_frand_neg1half_to_pos1half(random_seeds), rt_cl_frand_neg1half_to_pos1half(random_seeds), 0.);
		camray.pos *= (float3)(scene->camera.aperture);
		camray.dir = (float3)(x_id - width / 2, y_id - height / 2, fov_val);
		camray.dir += (float3)(rt_cl_frand_neg1half_to_pos1half(random_seeds) * 0.1, rt_cl_frand_neg1half_to_pos1half(random_seeds) * 0.1, 0.); //TODO, replace 0.1 by appropriate value; add and fix for depth of field
	}
	else if (scene->camera.model == CAMERA_MODEL_FOCAL)
	{
		seeds = (float2)(rt_cl_frand_0_to_1(random_seeds) / 2, rt_cl_frand_0_to_1(random_seeds) / 2);
		box_muller_sample = (float2)(sqrt(-2 * log((float)(seeds.x))) * cos(TAU * seeds.y), sqrt(-2 * log((float)(seeds.x))) * sin(TAU * seeds.y));
		camray.dir = (float3)(x_id - width / 2 + box_muller_sample.x, y_id - height / 2 + box_muller_sample.y, fov_val);
		camray.dir = normalize(camray.dir);
		aperture.x = rt_cl_frand_0_to_1(random_seeds) * scene->camera.aperture;
		aperture.y = rt_cl_frand_0_to_1(random_seeds) * scene->camera.aperture;
		camray.pos = (float3)(aperture.x, aperture.y, 0.);
		camray.dir = (scene->camera.focal_length * camray.dir) - camray.pos;
	}
	else if (scene->camera.model == CAMERA_MODEL_ORTHOGRAPHIC)
	{
		camray.pos = (float3)(x_id - width / 2, y_id - height / 2, 0.f);
		camray.pos *= (float3)(scene->camera.aperture);
		camray.dir = (float3)(0.f, 0.f, -1.f);
	}
	camray.pos = rt_cl_apply_homogeneous_matrix(cam_mat44, camray.pos);
	camray.dir = rt_cl_apply_linear_matrix(cam_mat44, camray.dir);
	camray.dir = normalize(camray.dir);
	return (camray);
}

//For some reason a statement with || doesn't EVER get read properly as a truth statement so I switched conditions around 
static float3			rt_cl_get_pixel_color_from_mc_sampling
(
					__constant		t_scene	*	scene,
									uint2 *		random_seeds
)
{
	float3				pixel_rgb = (float3)(0.);
	float const			inv_samp_size = 1. / scene->mc_raysamp_size;
	t_ray				ray_i;
	t_intersection		inter;

	for (uint i = 0; i < scene->mc_raysamp_size; ++i)
	{
		ray_i = rt_cl_create_camray(scene, random_seeds);
		for (uint depth = 0; !ray_i.complete && depth < scene->max_ray_depth; ++depth)
		{
			inter = rt_cl_trace_ray_to_scene(scene, &ray_i);
			if (inter)
			{
				if (scene->render_mode == RENDERMODE_MCPT)
				{
					ray_i = rt_cl_accumulate_lum_and_bounce_ray(scene, random_seeds, ray_i, i, depth);
				}
				else
				{
					return (scene->objects[ray_i.hit_obj_id].rgb);
				}
			}
			else
			{
				if (scene->render_mode == RENDERMODE_MCPT)
				{
					ray_i.complete = true;
					ray_i.lum_acc += ray_i.lum_mask * scene->bg_rgb;
				}
				else
				{
					return (scene->bg_rgb);
				}
			}
		}
		pixel_rgb += ray_i.lum_acc;
	}
	pixel_rgb *= (float3)(inv_samp_size); 
	return (pixel_rgb);
}


__kernel void			rt_cl_render
(
					__global		uint *		result_imgbuf,
					__constant		t_scene	*	scene
)
{
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;
	uint2				random_seeds;

	random_seeds.x = x_id;// ^ scene->random_seed_time;
	random_seeds.y = y_id;

/*if (work_item_id == 0)
{
	debug_print_scene(scene);
	debug_print_camera(&(scene->camera));
}*/
	rt_cl_rand(&random_seeds);
	float3 vcolor3 = rt_cl_get_pixel_color_from_mc_sampling(scene, &random_seeds);//rt_cl_f3rand_neg1half_to_pos1half(random_seed) * (float3)(255.);//
	vcolor3 = (float3)(255.) * fmin(vcolor3, (float3)(1.));
//	printf((__constant char *)"kernel %10g %10g %10g\n", vcolor3.x, vcolor3.y, vcolor3.z);
	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] = color;
}
