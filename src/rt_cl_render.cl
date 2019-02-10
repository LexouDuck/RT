

//#pragma OPENCL EXTENSION cl_intel_printf : enable
//#pragma OPENCL EXTENSION cl_amd_printf : enable
//#include "rt_cl_render.cl.h"

#include "src/rt_cl_random.cl"

#if 0

bool			get_realroots_quadpoly
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
		roots[0].x = 0. / 0.;
		roots[0].y = 0. / 0.;
		return (FALSE);
	}
	one_over_two_a = 0.5 / quadpoly.a;
	delta = sqrt(delta);
	roots[0].x = (-quadpoly.y + delta) * one_over_two_a;
	roots[0].y = (-quadpoly.y - delta) * one_over_two_a;
	return (TRUE);
}


/*
**	========================================================================
**
**							Intersection handling
**
**	========================================================================
*/

bool			ray_intersect_bbox
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
	tmin = fmax(tmin, fmax(tinf[0], fmax(tinf[1], tinf[2])));
	tmax = fmin(tmax, fmin(tsup[0], fmin(tsup[1], tsup[2])));

	//intersection iff no incoherence in all previous checks and tmin = Max(inferior bound) < Min(superior bound) = tmax
	return (tmin < tmax);
}

t_intersection			ray_intersect_sphere
(
							t_float *	res,
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
	if (roots.x <= 0.)
	{
		*res = roots.y;
		return (INTER_INSIDE);
	}
	if (roots.y <= 0.)
	{
		*res = roots.x;
		return (INTER_INSIDE);
	}
	*res = ft_fmin(root1, root2);
	return (INTER_OUTSIDE);
}


t_bool			trace_ray_to_scene
(
					__constant		t_scene		scene,
									t_ray *		ray
)
{
	uint			obj_id = -1;
	bool			inter;
	t_float			new_t;
	t_ray			res;

	for (int i = 0; i < scene.object_array_len; ++i)
	{
		inter = CL_FALSE;
		inter = ray_intersect_bbox(ray, scene.objects[i].bbox, 0, ray.t);
		if (inter)
		{
			inter = ray_intersect_sphere(&new_t, ray);
			if (inter)
			{
				ray->t = new_t;
				ray->hit_obj_id = i;
			}
		}
	}
	return (inter);
}

void			accumulate_lum_and_bounce_ray
(
									t_ray *		ray,
						__constant	t_scene		scene,				
)
{

}

float3			get_pixel_color_from_mc_sampling
(
					__constant		t_scene		scene,
					__local			uint		random_seed,
									int			x_id,
									int			y_id
)
{
	float3			res_pixel_color = (float3)(0.);
	float16	const	cam_mat44 = init_cam(scene.camera.world_pos, scene.camera.anchor, scene.camera.tilt);
	float const		fov_val = -get_global_size(0) / (2 * tan(scene.camera.hrz_fov));
	float3			cur_color;
	t_ray			ray_i;

	for (int i = 0; i < scene.mc_raysamp_size; ++i)
	{
		random_seed = DEFAULT_SEED + random_seed + x_id + y_id + i;
		ray_i.t = scene.render_dist;
		ray_i.pos = scene.camera.world_pos;
/*		ray_i.pos = (float3(0., 0., 0.);
		ray_i.pos += rt_cl_f3rand_0_to_1(random_seed) - (float3)(0.5, 0.5, 0.); //add and fix with camera.aperture for depth of field
		ray_i.pos = apply_homogeneous_matrix(cam_mat44, ray_i.pos);
*/		ray_i.dir = (float3)(x_id - get_global_size(0) / 2, y_id - get_global_size(1) / 2, fov_val);
/*		ray_i.dir += rt_cl_f3rand_0_to_1(random_seed) - (float3)(0.005, 0.005, 0.); //add and fix for anti-aliasing
*/		ray_i.dir = apply_linear_matrix(cam_mat44, ray_i.dir);
		ray_i.dir = normalize(ray_i.dir);
		cur_color = (float3)(0.);
		for (int depth = 0; !ray.complete && depth < scene.max_ray_depth; ++depth)
		{
		//	trace_ray_to_bboxes(ray, scene);
		//	trace_ray_to_primitives(ray, scene, index_list);
			if (trace_ray_scene(&ray_i, scene))
			{
				accumulate_lum_and_bounce_ray(&ray_i, scene);
			}
			else
			{
				ray.complete = CL_TRUE;
				cur_color = ray.lum_acc * BG_COLOR;
				break ;
			}
		}
		res_pixel_color = res_pixel_color + cur_color;
	}
	res_pixel_color = res_pixel_color;
}


__kernel void	rt_cl_render
(
					__global		uint *		result_imgbuf,
					__constant		t_scene		scene,
					__local			uint		random_seed
)
{
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;

	float3 vcolor3 = get_pixel_color_from_mc_sampling(scene, x_id, y_id);
	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] = color; /* simple interpolated colour gradient based on pixel coordinates */
}
#endif


__kernel void	rt_cl_render
(
					__global		uint *		result_imgbuf,
		//			__constant		t_scene		scene,
					__local			uint *		random_seed
)
{
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;

	*random_seed = DEFAULT_SEED * work_item_id + DEFAULT_SEED;
	float3 vcolor3 = rt_cl_f3rand_0_to_1(random_seed);
	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] = color; /* simple interpolated colour gradient based on pixel coordinates */
}