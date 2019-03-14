/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_render.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_intersection		rt_cl_primitive_get_inter
(
									float *			new_t,
									t_ray			ray_os,
									t_primitive		type
)
{
	t_intersection	inter;

	if (type == sphere)
		inter = rt_cl_sphere_intersect(new_t, ray_os);
	else if (type == plane)
		inter = rt_cl_plane_intersect(new_t, ray_os);
	else if (type == disk)
		inter = rt_cl_disk_intersect(new_t, ray_os);
	else if (type == rectangle)
		inter = rt_cl_rectangle_intersect(new_t, ray_os);
	else if (type == triangle)
		inter = rt_cl_triangle_intersect(new_t, ray_os);
	else if (type == cylinder)
		inter = rt_cl_cylinder_intersect(new_t, ray_os);
	else if (type == cone)
		inter = rt_cl_cone_intersect(new_t, ray_os);
	else if (type == infcylinder)
		inter = rt_cl_infcylinder_intersect(new_t, ray_os);
	else if (type == infcone)
		inter = rt_cl_infcone_intersect(new_t, ray_os);
	else if (type == cube)
		inter = rt_cl_cube_intersect(new_t, ray_os);
	else if (type == paraboloid)
		inter = rt_cl_paraboloid_intersect(new_t, ray_os);
	else if (type == hyperboloid)
		inter = rt_cl_hyperboloid_intersect(new_t, ray_os);
	else if (type == saddle)
		inter = rt_cl_saddle_intersect(new_t, ray_os);
	else
		inter = INTER_NONE;
	return (inter);
}

static float3		rt_cl_primitive_get_normal
(
									float3			hitpos,
									t_primitive		type
)
{
	float3		normal_os;

	if (type == sphere)
		normal_os = rt_cl_sphere_get_normal(hitpos);
	else if (type == plane || type == disk || type == rectangle || type == triangle)
		normal_os = rt_cl_plane_get_normal(hitpos);
	else if (type == cylinder)
		normal_os = rt_cl_cylinder_get_normal(hitpos);
	else if (type == infcylinder)
		normal_os = rt_cl_infcylinder_get_normal(hitpos);
	else if (type == infcone)
		normal_os = rt_cl_infcone_get_normal(hitpos);
	else if (type == cone)
		normal_os = rt_cl_cone_get_normal(hitpos);
	else if (type == cube)
		normal_os = rt_cl_cube_get_normal(hitpos);
	else if (type == paraboloid)
		normal_os = rt_cl_paraboloid_get_normal(hitpos);
	else if (type == hyperboloid)
		normal_os = rt_cl_hyperboloid_get_normal(hitpos);
	else if (type == saddle)
		normal_os = rt_cl_saddle_get_normal(hitpos);
	else
		normal_os = rt_cl_sphere_get_normal(hitpos);
	return (normal_os);
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
	__constant	t_object *			obj;
				t_intersection		bbox_ws_inter;
				t_intersection		bbox_os_inter;
				t_intersection		prim_inter;
				float				tmax;
				float				new_tbbox_ws;
				float				new_tbbox_os;
				float				new_t;
				t_ray				ray_os;
				t_ray				result_ray_os;

	tmax = ray->t;
	prim_inter = INTER_NONE;
	for (uint i = 0; i < scene->object_amount; ++i)
	{
		obj = &(scene->objects[i]);
		bbox_ws_inter = rt_cl_ray_intersect_bbox(*ray, obj->bbox_ws, 0.f, tmax, &new_tbbox_ws);
		if (bbox_ws_inter) 
		{
			if (scene->render_mode == RENDERMODE_BBOX_WS)
			{
				tmax = new_tbbox_ws;
				ray->t = new_tbbox_ws;
				ray->hit_obj_id = i;
				prim_inter = bbox_ws_inter;
			}
			else
			{
				ray_os = *ray;
				ray_os.inter_type = INTER_NONE;
				ray_os.pos = rt_cl_apply_homogeneous_matrix(obj->w_to_o, ray_os.pos);
				ray_os.dir = rt_cl_apply_linear_matrix(obj->w_to_o, ray_os.dir);//DO NOT NORMALIZE: YOU NEED TO KEEP ray.t CONSISTENT

				bbox_os_inter = rt_cl_ray_intersect_bbox(ray_os, obj->bbox_os, 0.f, tmax, &new_tbbox_os);
				if (bbox_os_inter)
				{
					if (scene->render_mode == RENDERMODE_BBOX_OS)
					{
						tmax = new_tbbox_os;
						ray->t = new_tbbox_os;
						ray->hit_obj_id = i;
						prim_inter = bbox_os_inter;
					}
					else
					{
						ray_os.inter_type = rt_cl_primitive_get_inter(&new_t, ray_os, obj->type);
						if (ray_os.inter_type && EPS < new_t && new_t < ray->t)
						{
							ray_os.hitpos = ray_os.pos + ((float3)new_t) * ray_os.dir;
							if (rt_cl_point_is_in_bbox(ray_os.hitpos, obj->bbox_os))
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
			}
		}
	}
	if ((scene->render_mode != RENDERMODE_BBOX_WS) && 
		(scene->render_mode != RENDERMODE_BBOX_OS) &&
		prim_inter)
		*ray = result_ray_os;

//if (get_global_id(0) == 320 && get_global_id(1) == 240)	printf("color in end of trace %f %f %f\n", ray->lum_acc.x, ray->lum_acc.y, ray->lum_acc.z);
	return (prim_inter);
}

static t_ray			rt_cl_accumulate_lum_and_bounce_ray
(

						__constant	t_scene	*	scene,
						__constant	uint *		img_texture,
									uint2 *		random_seeds,
									t_ray *		ray
)
{
	__constant	t_object *	obj = &(scene->objects[ray->hit_obj_id]);
				t_ray		new_ray;
				float3		hitpos;
				float3		normal;
				t_texture	texture;
				bool		is_inter_inside;

	hitpos = ray->hitpos;
	normal = ray->inter_type * rt_cl_primitive_get_normal(hitpos, obj->type);
	is_inter_inside = (ray->inter_type == INTER_INSIDE);	

	texture = rt_cl_get_texture_properties(scene, obj, img_texture, random_seeds, (hitpos - normal * (float3)(EPS)), normal);

//if (get_global_id(0) == 320 && get_global_id(1) == 240)	printf("color in lumacc %f %f %f\n", ray->lum_acc.x, ray->lum_acc.y, ray->lum_acc.z);
	if (scene->render_mode == RENDERMODE_SOLIDTEXTURE)
	{
		new_ray.lum_acc = texture.rgb * ray->lum_mask;
		return (new_ray);
	}
	normal = texture.bump_normal;
	if (scene->render_mode == RENDERMODE_NORMALS)
	{
		normal = rt_cl_apply_linear_matrix(obj->n_to_w, normal);
		new_ray.lum_acc = fabs(normalize(normal));
		return (new_ray);
	}

	new_ray.refrac = ray->refrac;
	new_ray.hit_obj_id = -1;
	new_ray.inter_type = INTER_NONE;
	new_ray.t = scene->render_dist;
	new_ray.complete = (obj->material == light);//TODO add a cutoff for minimal contributions ?
	new_ray.lum_acc = ray->lum_acc;
	
	if (new_ray.complete)
	{
		new_ray.lum_acc += ray->lum_mask * texture.rgb; //TODO test with "* dot(normal, -ray.dir)" weighing ?
		return (new_ray);
	}

	else if (obj->material == diffuse)
	{
		new_ray.dir = rt_cl_rand_dir_coshemi(random_seeds, normal);
		new_ray.lum_mask = ray->lum_mask * texture.rgb * (float3)(dot(normal, new_ray.dir));//cos sampling, defines contribution to ray.lum_acc
	}
	else if (obj->material == transparent)
	{
		new_ray.lum_mask = ray->lum_mask;
		float	prev_refrac = ray->refrac;
		float	new_refrac	= (is_inter_inside) ?
								ray->refrac / obj->refrac : //TODO replace with a stored obj->inv_refrac and init in build_scene ?
								ray->refrac * obj->refrac;
		bool	is_transmitted;

		is_transmitted = rt_cl_get_transmit_or_reflect(&new_ray.dir, random_seeds, ray->dir, normal, prev_refrac, new_refrac, obj->roughness);
		//new_ray.lum_mask = ray.lum_mask * texture.rgb; //TODO replace with this line and return texture.rgb = 1.1.1. for inter_outside and an average of samples for inter_inside
		new_ray.refrac = is_transmitted ? new_refrac : prev_refrac;
		new_ray.lum_mask = (!is_inter_inside && is_transmitted) || (is_inter_inside && !is_transmitted) ?
			ray->lum_mask * texture.rgb :
			ray->lum_mask;

		//Position correction for transmission
		if (is_transmitted)
			hitpos = mad(-2.f * EPS, normal, hitpos);//TODO @Hugo beware with textures for this call
	}
	else if (obj->material == specular)
	{
		new_ray.dir = rt_cl_get_reflect_coslobe(random_seeds, ray->dir, normal, obj->roughness);
		new_ray.lum_mask = ray->lum_mask * texture.rgb * (float3)(dot(normal, new_ray.dir));//*dot(new_dir, reflect) ?
	}
	hitpos = (float3)(EPS) * normal + hitpos;//TODO @Hugo maybe textures should take care of this call actually ?
	new_ray.pos = rt_cl_apply_homogeneous_matrix(obj->o_to_w, hitpos);
	new_ray.dir = rt_cl_apply_linear_matrix(obj->o_to_w, new_ray.dir);

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
	int const			width = scene->work_dims.x;
	int const			height = scene->work_dims.y;
	float16	const		cam_mat44 = scene->camera.c_to_w;
	float const			fov_val = -width / (2.f * tan(scene->camera.hrz_fov));
	t_ray				camray;
	float2				seeds;
	float2				box_muller_sample;
	float3				aperture;


	camray.t = scene->render_dist;
	camray.hit_obj_id = -1;
	camray.hitpos = (float3)(0.f);
	camray.lum_mask = scene->camera.rgb_mask;
	camray.lum_acc = scene->camera.rgb_shade;
	camray.refrac = 1.f;//TODO make "is in primitive" functions
	camray.inter_type = INTER_NONE;
	camray.complete = false;


	if (scene->camera.model == CAMERA_MODEL_PINHOLE)
	{
		camray.pos = (float3)(0.f, 0.f, 0.f);
		camray.dir = (float3)(x_id - width / 2, y_id - height / 2, fov_val);
	}
	else if (scene->camera.model == CAMERA_MODEL_BLUR_SIMPLE)
	{
		camray.pos = (float3)(rt_cl_frand_neg1half_to_pos1half(random_seeds),
							rt_cl_frand_neg1half_to_pos1half(random_seeds),
							0.f);
		camray.pos *= (float3)(scene->camera.aperture);
		camray.dir = (float3)(x_id - width / 2, y_id - height / 2, fov_val);
		camray.dir +=	(float3)
						(
							rt_cl_frand_neg1half_to_pos1half(random_seeds) * scene->camera.focal_dist,
							rt_cl_frand_neg1half_to_pos1half(random_seeds) * scene->camera.focal_dist,
							0.f
						);
	}
	else if (scene->camera.model == CAMERA_MODEL_BLUR_FOCAL)
	{
		seeds = (float2)(rt_cl_frand_0_to_1(random_seeds) / 2,
						rt_cl_frand_0_to_1(random_seeds) / 2);
		box_muller_sample = (float2)(sqrt(-2.f * log((float)(seeds.x))) * cos((float)(TAU * seeds.y)),
									sqrt(-2.f * log((float)(seeds.x))) * sin((float)(TAU * seeds.y)));
		camray.dir = (float3)(x_id - width / 2 + box_muller_sample.x, y_id - height / 2 + box_muller_sample.y, fov_val);
		camray.dir = normalize(camray.dir);
		aperture.x = rt_cl_frand_0_to_1(random_seeds) * scene->camera.aperture;
		aperture.y = rt_cl_frand_0_to_1(random_seeds) * scene->camera.aperture;
		camray.pos = (float3)(aperture.x, aperture.y, 0.f);
		camray.dir = (scene->camera.focal_dist * camray.dir) - camray.pos;
	}
	else if (scene->camera.model == CAMERA_MODEL_AUTO_FOCUS)
	{
		seeds = (float2)(rt_cl_frand_0_to_1(random_seeds) / 2,
						rt_cl_frand_0_to_1(random_seeds) / 2);
		box_muller_sample = (float2)(sqrt(-2.f * log((float)(seeds.x))) * cos((float)(TAU * seeds.y)),
									sqrt(-2.f * log((float)(seeds.x))) * sin((float)(TAU * seeds.y)));
		camray.dir = (float3)(x_id - width / 2 + box_muller_sample.x, y_id - height / 2 + box_muller_sample.y, fov_val);
		camray.dir = normalize(camray.dir);
		aperture.x = rt_cl_frand_0_to_1(random_seeds) * scene->camera.aperture;
		aperture.y = rt_cl_frand_0_to_1(random_seeds) * scene->camera.aperture;
		camray.pos = (float3)(aperture.x, aperture.y, 0.f);
		camray.dir = (scene->camera.zoom * camray.dir) - camray.pos;	
	}
	else if (scene->camera.model == CAMERA_MODEL_ORTHOGRAPHIC)
	{
		camray.pos = (float3)(x_id - width / 2, y_id - height / 2, 0.f);
		camray.pos *= (float3)(scene->camera.aperture / scene->camera.zoom);
		camray.dir = (float3)(0.f, 0.f, -1.f);
	}
	camray.pos = rt_cl_apply_homogeneous_matrix(cam_mat44, camray.pos);
	camray.dir = rt_cl_apply_linear_matrix(cam_mat44, camray.dir);
	camray.dir = normalize(camray.dir);

	return (camray);
}
 
static float3			rt_cl_get_ray_pixel_contribution
(
					__constant		t_scene	*	scene,
					__constant		uint *		img_texture,
									uint2 *		random_seeds
)
{
	t_ray				ray_i;
	t_ray				tmp;
	t_intersection		inter;

	ray_i = rt_cl_create_camray(scene, random_seeds);
	for (uint depth = 0; !ray_i.complete && depth < scene->max_ray_depth; ++depth)
	{
		inter = rt_cl_trace_ray_to_scene(scene, &ray_i);
		if (inter)
		{
//if (get_global_id(0) == 320 && get_global_id(1) == 240)	printf("color in main %f %f %f depth %u\n", ray_i.lum_acc.x, ray_i.lum_acc.y, ray_i.lum_acc.z, depth);
			if (scene->render_mode == RENDERMODE_MCPT)
			{
				tmp = rt_cl_accumulate_lum_and_bounce_ray(scene, img_texture, random_seeds, &ray_i);
				ray_i = tmp;
			}
			else if ((scene->render_mode == RENDERMODE_SOLIDTEXTURE) || (scene->render_mode == RENDERMODE_NORMALS))
			{
				tmp = rt_cl_accumulate_lum_and_bounce_ray(scene, img_texture, random_seeds, &ray_i);
				return (tmp.lum_acc);
			}
			else
			{
				if (inter == INTER_INSIDE)
					return (scene->objects[ray_i.hit_obj_id].rgb_b);
				else
					return (scene->objects[ray_i.hit_obj_id].rgb_a);
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
	return (ray_i.lum_acc);
}


__kernel void			rt_cl_render
(
					__global		float3 *	rays_pp_tensor,
					__constant		t_scene	*	scene,
					__constant		uint *		img_texture
)
{
	size_t const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	size_t const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
	size_t const			block_x_id = x_id - get_global_offset(0); /* x-coordinate of the current pixel */
	size_t const			block_y_id = y_id - get_global_offset(1); /* y-coordinate of the current pixel */
	size_t const			ray_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/

	if (x_id >= scene->work_dims.x || y_id >= scene->work_dims.y || ray_id >= scene->work_dims.z)
	{
		return ;
	}

	size_t const			block_width = get_global_size(0);
	size_t const			block_height = get_global_size(1);
	size_t const			work_item_id = block_height * block_width * ray_id
										+					block_width * (block_y_id)
										+								 (block_x_id);
	uint2				random_seeds;
	float3				ray_lum_acc;

/*	if (x_id == 50 && y_id == 100 && ray_id == 0)
	{
		printf("render blocx %zu blocy %zu\n", block_x_id, block_y_id);
	}
*/
	random_seeds.x = x_id ^ ray_id + y_id;// + ray_id;// ^ scene->random_seed_time) + ray_id;
	random_seeds.y = y_id ^ ray_id + x_id * ray_id;// + scene->random_seed_time;// ^ (27309 * scene->random_seed_time - 0x320420C57 + ray_id);
	rt_cl_rand(&random_seeds);

	ray_lum_acc = rt_cl_get_ray_pixel_contribution(scene, img_texture, &random_seeds);
	rays_pp_tensor[work_item_id] = ray_lum_acc;
}


__kernel void			rt_cl_average
(
					__global		uint *				result_imgbuf,
					__global		float3 *			rays_pp_tensor,
					__constant		uint8 *				tensor_dims_arg
)
{
	uint3 const			work_steps = tensor_dims_arg->s012; /* work_step.xyz */
	uint3 const			work_dims = tensor_dims_arg->s456; /* work_dims.xyz, or equivalently (float3)(canvas_w, canvas_h, mc_raysamp_size) */
	size_t const		x_id = get_global_id(0); /* x-coordinate of the current pixel */
	size_t const		y_id = get_global_id(1); /* y-coordinate of the current pixel */

	if (x_id >= work_dims.x || y_id >= work_dims.y)
	{
		return ;
	}

	size_t const		block_x_id = x_id - get_global_offset(0); /* x-coordinate of the current pixel in current tensor block */
	size_t const		block_y_id = y_id - get_global_offset(1); /* y-coordinate of the current pixel in current tensor block */
	size_t const		work_item_id = work_dims.x * y_id
													+ x_id;
	size_t const		init = get_global_size(0) * block_y_id //work_steps.x * block_y_id
											+ block_x_id;
	size_t const		inc = work_steps.y * work_steps.x;
	size_t const		tensor_size = inc * work_dims.z; // we need the full ray dimension of the tensor for a quick average
	float const			inv_samp_size = native_recip((float)work_dims.z);
	float3				vcolor3 = (float3)(0.f);
	uint3				color3;
	uint				color;


//	int					ray_global_id;

	#pragma unroll
	for (uint i = init; i < tensor_size; i += inc)
	{
		vcolor3 += rays_pp_tensor[i];
	}
/*
	#pragma unroll
	for (int i = 0; i < tensor_dims.z; ++i)
	{
		ray_global_id = tensor_dims.y * tensor_dims.x * i
					+					tensor_dims.x * y_id
					+									x_id;
		vcolor3 += rays_pp_tensor[ray_global_id];
	}
*/
	vcolor3 *= (float3)(inv_samp_size);
	vcolor3 = (float3)(255.f) * fmin(vcolor3, (float3)(1.f));
	color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
	color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
	result_imgbuf[work_item_id] = color;
}