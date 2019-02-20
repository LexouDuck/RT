static bool			get_realroots_quadpoly
(
							float2 *	roots,
							float3		quadpoly
)
{
	float		delta;
	float		one_over_two_a;

	delta = quadpoly.y * quadpoly.y - 4 * quadpoly.x * quadpoly.z;
	if (delta < 0.)
	{
		roots->x = roots->y = 0. / 0.;
		return (false);
	}
	one_over_two_a = 0.5 / quadpoly.x;
	delta = sqrt(delta);
	roots->x = (-quadpoly.y + delta) * one_over_two_a;
	roots->y = (-quadpoly.y - delta) * one_over_two_a;
	return (true);
}

static bool			ray_intersect_bbox
(
					t_ray		ray,
					t_bbox		aabb,
					float		tmin,
					float		tmax/*,
					float *		tres*/
)
{
//	bool	inter;
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
	return (tmin < tmax);
}

static t_intersection			ray_intersect_sphere
(
							float *		res,
							t_ray		ray
)
{
	float3		quadpoly;
	float2		roots;

	quadpoly.x = dot(ray.dir, ray.dir);
	quadpoly.y = 2. * dot(ray.dir, ray.pos);
	quadpoly.z = dot(ray.pos, ray.pos) - 1.;
	if (!(get_realroots_quadpoly(&roots, quadpoly)))
		return (INTER_NONE);
	if ((roots.x <= 0. && roots.y <= 0.) ||
		(roots.x > ray.t && roots.y > ray.t))
		return (INTER_NONE);
	else if (roots.x <= 0.)
	{
		*res = roots.y;
		return (INTER_INSIDE);
	}
	else if (roots.y <= 0.)
	{
		*res = roots.x;
		return (INTER_INSIDE);
	}
	else
	{
		*res = fmin(roots.x, roots.y);
		return (INTER_OUTSIDE);
	}
}


static t_ray			trace_ray_to_scene
(
					__constant		t_scene	*	scene,
									t_ray		ray
)
{
//	bool			inter;
	float			new_t;
	t_ray			ray_os;
	t_ray			result_ray_os;

	for (uint i = 0; i < scene->object_amount; ++i)
	{
		if (ray_intersect_bbox(ray, scene->objects[i].bbox, 0, ray.t))
		{
			ray_os = ray;
			ray_os.inter_type = INTER_NONE;
			ray_os.pos = rt_cl_apply_homogeneous_matrix(scene->objects[i].w_to_o, ray_os.pos);
			ray_os.dir = rt_cl_apply_linear_matrix(scene->objects[i].w_to_o, ray_os.dir);//DO NOT NORMALIZE: YOU NEED TO KEEP ray.t CONSISTENT
			ray_os.inter_type = ray_intersect_sphere(&new_t, ray_os);
			if (ray_os.inter_type)
			{	
				ray.inter_type = ray_os.inter_type;
				result_ray_os = ray_os;
				result_ray_os.hit_obj_id = i;
				ray.t = new_t;
				result_ray_os.t = new_t;
			}
		}
	}
	return (ray.inter_type ? result_ray_os : ray);
}


static t_ray			accumulate_lum_and_bounce_ray
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



//	ray->lum_mask *= obj->rgb;


//if (sampid == 0 && depth == 0) printf("%g %g %g   %g %g %g   %g  %d  %d \n", ray.pos.x, ray.pos.y, ray.pos.z, ray.dir.x, ray.dir.y, ray.dir.z, ray.t, ray.hit_obj_id, ray.inter_type);
	hitpos = ray.pos + ((float3)(ray.t)) * ray.dir;
//if (sampid == 0 && depth == 0) printf("hitpos %g %g %g\n", hitpos.x, hitpos.y, hitpos.z);
//if (sampid == 0 && depth == 0) printf("%g %g %g   %g %g %g   %g  %d  %d | %g %g %g\n", ray.pos.x, ray.pos.y, ray.pos.z, ray.dir.x, ray.dir.y, ray.dir.z, ray.t, ray.hit_obj_id, ray.inter_type, hitpos.x, hitpos.y, hitpos.z);
//if (sampid == 0 && depth == 0){float16 nw = obj->n_to_w; printf("\tobj->n_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n", nw.s0, nw.s1, nw.s2, nw.s3, nw.s4, nw.s5, nw.s6, nw.s7, nw.s8, nw.s9, nw.sA, nw.sB, nw.sC, nw.sD, nw.sE, nw.sF);}
	normal = rt_cl_apply_linear_matrix(obj->n_to_w, hitpos);// * (float3)(ray.inter_type);
//if (sampid == 0 && depth == 0) printf("normal %f %f %f | %g\n", normal.x, normal.y, normal.z, (float)dot(normal, normal));
	normal = normalize(normal); //sphere formula, normal == hitpos
//if (depth == 0) printf("normal %f %f %f\n", normal.x, normal.y, normal.z);
	new_ray.pos = rt_cl_apply_homogeneous_matrix(obj->o_to_w, hitpos) + normal * (float3)(EPS);
	new_ray.dir = rt_cl_rand_dir_coshemi(random_seeds, normal);
//if (sampid == 0 && depth == 1) printf("normal %f %f %f => %f | hitpos %f %f %f \n", normal.x, normal.y, normal.z, (float)dot(normal, normal), new_ray.pos.x, new_ray.pos.y, new_ray.pos.z);

//if (sampid == 0 && depth == 0) printf("dir %f %f %f => %f | mask %f %f %f \n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z, (float)dot(new_ray.dir, new_ray.dir), new_ray.lum_mask.x, new_ray.lum_mask.y, new_ray.lum_mask.z);
//	new_ray.dir = normalize(rt_cl_f3rand_neg1half_to_pos1half(random_seed));
	new_ray.hit_obj_id = -1;
	new_ray.inter_type = INTER_NONE;
	new_ray.t = scene->render_dist;
	if (obj->material == lightsrc)
	{
		new_ray.complete = true;
		new_ray.lum_mask = ray.lum_mask;
		new_ray.lum_acc = ray.lum_acc + ray.lum_mask * obj->light;//obj->rgb;
//	if(sampid == 0 && depth == 0)	
//		printf("acc %f %f %f\n", obj->rgb.x, obj->rgb.y, obj->rgb.z);//ray->lum_mask.x, ray->lum_mask.y, ray->lum_mask.z);//new_ray.lum_acc.x, new_ray.lum_acc.y, new_ray.lum_acc.z);
	}
	else
	{
		new_ray.complete = false;
		new_ray.lum_mask = ray.lum_mask * obj->rgb * (float3)(dot(normal, new_ray.dir));
		new_ray.lum_acc = ray.lum_acc;// + ray.lum_mask;
	}

//	if (sampid == 0 && depth == 0) printf("normal %f %f %f => %f | hitpos %f %f %f \n", normal.x, normal.y, normal.z, (float)dot(normal, normal), new_ray.pos.x, new_ray.pos.y, new_ray.pos.z);
//	if (sampid == 0 && depth == 0) printf("dir %f %f %f => %f | mask %f %f %f \n", new_ray.dir.x, new_ray.dir.y, new_ray.dir.z, (float)dot(new_ray.dir, new_ray.dir), new_ray.lum_mask.x, new_ray.lum_mask.y, new_ray.lum_mask.z);
	return (new_ray);
}



static float3			get_pixel_color_from_mc_sampling
(
					__constant		t_scene	*	scene,	
									uint2 *		random_seeds,
									int			x_id,
									int			y_id
)
{
	float3				pixel_rgb = (float3)(0.);
	int const			width = get_global_size(0);
	int const			height = get_global_size(1);
	float16	const		cam_mat44 = scene->camera.c_to_w;
	float const			fov_val = -width / (2 * tan(scene->camera.hrz_fov));
	float const			inv_samp_size = 1. / scene->mc_raysamp_size;
	t_ray				ray_i;

	for (uint i = 0; i < scene->mc_raysamp_size; ++i)
	{
		ray_i.lum_acc = (float3)(0.);
		ray_i.lum_mask = (float3)(1.);
		ray_i.t = scene->render_dist;
		ray_i.complete = false;
		ray_i.hit_obj_id = -1;
		ray_i.inter_type = INTER_NONE;
		ray_i.pos = (float3)(0., 0., 0.);
//		ray_i.pos = (float3)(rt_cl_frand_neg1half_to_pos1half(random_seeds), rt_cl_frand_neg1half_to_pos1half(random_seeds), 0.); //add and fix with camera.aperture for depth of field
//		ray_i.pos *= (float3)(scene->camera.aperture);
		ray_i.pos = rt_cl_apply_homogeneous_matrix(cam_mat44, ray_i.pos);
//		if (i = 0) printf("%f %f %f\n", ray_i.pos.x, ray_i.pos.y, ray_i.pos.z);
		ray_i.dir = (float3)(x_id - width / 2, y_id - height / 2, fov_val);
//		ray_i.dir += (float3)(rt_cl_frand_neg1half_to_pos1half(random_seed) * 0.1, rt_cl_frand_neg1half_to_pos1half(random_seed) * 0.1, 0.); //add and fix for anti-aliasing
		ray_i.dir = rt_cl_apply_linear_matrix(cam_mat44, ray_i.dir);
		ray_i.dir = normalize(ray_i.dir);

		for (uint depth = 0; !ray_i.complete && depth < scene->max_ray_depth; ++depth)
		{

		//	trace_ray_to_bboxes(ray, scene);
		//	trace_ray_to_primitives(ray, scene, index_list);
			ray_i = trace_ray_to_scene(scene, ray_i);
			if (ray_i.inter_type)
			{
//				return scene->objects[ray_i.hit_obj_id].rgb;
				ray_i = accumulate_lum_and_bounce_ray(scene, random_seeds, ray_i, i, depth);
//				if (ray_i.complete)
//					break ;
			}
			else
			{
//				return (0xFF000000);
				ray_i.complete = true;
				ray_i.lum_acc += ray_i.lum_mask * scene->bg_rgb;
				//break;
			}
		}
		pixel_rgb += ray_i.lum_acc;
//		if (i = 0) printf("%f %f %f\n", ray_i.pos.x, ray_i.pos.y, ray_i.pos.z);//ray_i.lum_acc.x, ray_i.lum_acc.y, ray_i.lum_acc.z);//res_pixel_color.x, res_pixel_color.y, res_pixel_color.z);
	}
	pixel_rgb *= (float3)(inv_samp_size); 
	return (pixel_rgb);
}


__kernel void	rt_cl_render
(
					__global		uint *		result_imgbuf,
					__constant		t_scene	*	scene//,
//										uint		random_seed[1]
)
{	
//	int const			width = get_global_size(0);
//	int const			height = get_global_size(1);
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;
//				uint		random_seed[1];
	uint2				random_seeds;

	random_seeds.x = x_id;// ^ scene->random_seed_time;
	random_seeds.y = y_id;

/*if (work_item_id == 0)
{
	debug_print_scene(scene);
	debug_print_camera(&(scene->camera));
}*/
	rt_cl_rand(&random_seeds);
	float3 vcolor3 = (float3)(255.) * get_pixel_color_from_mc_sampling(scene, &random_seeds, x_id, y_id);//rt_cl_f3rand_neg1half_to_pos1half(random_seed) * (float3)(255.);//
//	printf((__constant char *)"kernel %10g %10g %10g\n", vcolor3.x, vcolor3.y, vcolor3.z);
	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] = color; /* simple interpolated colour gradient based on pixel coordinates */
}
