

//#pragma OPENCL EXTENSION cl_intel_printf : enable
//#pragma OPENCL EXTENSION cl_amd_printf : enable
//#include "rt_cl_render.cl.h"

//#include "src/rt_cl.h"
#include "src/rt_cl_scene.cl.h"
#include "src/rt_cl_random.cl"
#include "src/rt_cl_build_scene.cl"

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
		roots->x = roots->y = 0. / 0.;
		return (false);
	}
	one_over_two_a = 0.5 / quadpoly.x;
	delta = sqrt(delta);
	roots->x = (-quadpoly.y + delta) * one_over_two_a;
	roots->y = (-quadpoly.y - delta) * one_over_two_a;
	return (true);
}

/*
** ************************************************************************** *|
**	                        Intersection handling                             *|
** ************************************************************************** *|
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
	tmin = fmax(tmin, fmax(tinf.x, fmax(tinf.y, tinf.z)));
	tmax = fmin(tmax, fmin(tsup.x, fmin(tsup.y, tsup.z)));

	//intersection iff no incoherence in all previous checks and tmin = Max(inferior bound) < Min(superior bound) = tmax
	return (tmin < tmax);
}

t_intersection			ray_intersect_sphere
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
	*res = fmin(roots.x, roots.y);
	return (INTER_OUTSIDE);
}


bool			trace_ray_to_scene
(
					__constant		t_scene	*	scene,
									t_ray *		ray,
									uint		depth
)
{
//	uint			obj_id = -1;
	bool			inter;
	float			new_t;
	t_ray			ray_os;
	t_ray			new_ray;

	inter = false;
	for (uint i = 0; i < scene->object_amount; ++i)
	{
		if (ray_intersect_bbox(*ray, scene->objects[i].bbox, 0, ray->t))
		{
//if (depth == 0 && i == 0) printf("a");
			ray_os = *ray;
			ray_os.pos = rt_cl_apply_homogeneous_matrix(scene->objects[i].w_to_o, ray_os.pos);
			ray_os.dir = rt_cl_apply_linear_matrix(scene->objects[i].w_to_o, ray_os.dir);
			ray_os.dir = normalize(ray_os.dir);
			if (ray_intersect_sphere(&new_t, ray_os))
			{	
				inter = true;
				new_ray = ray_os;
				new_ray.hit_obj_id = i;
				ray->t = new_ray.t = new_t;
			}
			//else ; 
		}
		//else ;
	}
	if (inter)
		*ray = new_ray;
	return (inter);
}

void			accumulate_lum_and_bounce_ray
(
									t_ray *		ray,
						__constant	t_scene	*	scene,
						__local		uint *		random_seed,
									int			depth		
)
{
	__constant t_object		*obj = &(scene->objects[ray->hit_obj_id]);

	t_ray		new_ray;
	float3		normal;
	float3		hitpos;
/*

		hit obj
		quaddist = ray.t * ray.t;
		costh = dot(normal, objshdr.out_ray_ws.dir);
		vec3_scale(reslum.vec,
			INV_PI * lgtshdr.hit_obj->intensity * ft_fmax(0., costh) / quaddist,
			objshdr.hit_obj->rgb.vec);

		hit light
		vec3_schur(reslum.vec, reslum.vec, lgtshdr.hit_obj->rgb.vec);
*/

	ray->lum_mask *= obj->rgb * (float3)(depth > 0 ? 1. : 1. / (ray->t * ray->t));
	if (obj->material == lightsrc)
	{
		ray->complete = true;
		return ;
	}
	else
	{
		hitpos = ray->pos + (float3)ray->t * ray->dir;
		new_ray.pos = rt_cl_apply_homogeneous_matrix(obj->o_to_w, hitpos);
		normal = normalize(rt_cl_apply_linear_matrix(obj->n_to_w, hitpos)); //sphere formula, normal == hitpos
		new_ray.dir = rt_cl_rand_dir_hemi(random_seed, normal);
		new_ray.complete = false;
		new_ray.hit_obj_id = -1;
		new_ray.t = scene->render_dist;
		new_ray.lum_mask = ray->lum_mask * (float3)(INV_PI * fmax((float)0., (float)dot(normal, new_ray.dir)));






		*ray = new_ray;
	}
}

/*
** If else probably linked to older hardware pb.
** https://computergraphics.stackexchange.com/questions/4115/gpu-branching-if-without-else
*/
float3			get_pixel_color_from_mc_sampling
(
					__constant		t_scene	*	scene,
					__local			uint *		random_seed,
									int			x_id,
									int			y_id
)
{
	float3			res_pixel_color = (float3)(0.);
	float16	const	cam_mat44 = scene->camera.c_to_w;
	float const		fov_val = -get_global_size(0) / (2 * tan(scene->camera.hrz_fov));
//	float3			cur_color;
	t_ray			ray_i;

//printf("scene2 %f  ", scene->camera.c_to_w.sF);
	for (uint i = 0; i < scene->mc_raysamp_size; ++i)
	{
		random_seed = DEFAULT_SEED + random_seed + x_id + y_id + i;
		ray_i.t = scene->render_dist;
		ray_i.complete = false;
		ray_i.hit_obj_id = -1;
		ray_i.pos = scene->camera.world_pos;
/*		ray_i.pos = (float3(0., 0., 0.);
		ray_i.pos += rt_cl_f3rand_0_to_1(random_seed) - (float3)(0.5, 0.5, 0.); //add and fix with camera.aperture for depth of field
		ray_i.pos = apply_homogeneous_matrix(cam_mat44, ray_i.pos);
*/		ray_i.dir = (float3)(x_id - get_global_size(0) / 2, y_id - get_global_size(1) / 2, fov_val);
/*		ray_i.dir += rt_cl_f3rand_0_to_1(random_seed) - (float3)(0.005, 0.005, 0.); //add and fix for anti-aliasing
*/		ray_i.dir = rt_cl_apply_linear_matrix(cam_mat44, ray_i.dir);
		ray_i.dir = normalize(ray_i.dir);
		ray_i.lum_mask = (float3)(1.);
/*		if (isequal((float)scene->camera.c_to_w.sF, (float)0.))
		{
			return ((float3)(0., 255., 0.));
		}
		else if (isequal((float)scene->camera.c_to_w.sF, (float)0.5))
		{
			return ((float3)(255., 0., 255.));
		}
		else
			return ((float3)(255., 255., 0.));
*/		for (uint depth = 0; !ray_i.complete && depth < scene->max_ray_depth; ++depth)
		{
		//	trace_ray_to_bboxes(ray, scene);
		//	trace_ray_to_primitives(ray, scene, index_list);
			if (trace_ray_to_scene(scene, &ray_i, depth))
			{
				accumulate_lum_and_bounce_ray(&ray_i, scene, random_seed, depth);
			}			
//printf("hit_obj = %d | depth = %d\n", ray_i.hit_obj_id);
			else
			{
				ray_i.complete = true;
				ray_i.lum_mask = ray_i.lum_mask * scene->bg_rgb;
			}
		}
		res_pixel_color = res_pixel_color + ray_i.lum_mask;
	}
	res_pixel_color = res_pixel_color * (float3)(1. / scene->mc_raysamp_size); //TODO 1/MCRSS can be precalculated
	return (res_pixel_color);
}


__kernel void	rt_cl_render
(
					__global		uint *		result_imgbuf,
					__constant		t_scene	*	scene,
					__local			uint *		random_seed
)
{
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;


//float16		tmp;
	__constant t_object *	obj = &(scene->objects[0]);
printf((__constant char *)"pos : %f %f %f | scale %f %f %f | rot %f %f %f \n", obj->pos.x, obj->pos.y, obj->pos.z, obj->scale.x, obj->scale.y, obj->scale.z, obj->rot.x, obj->rot.y, obj->rot.z);

/*tmp = rt_cl_mat44_transpose(obj->w_to_o);
printf("obj->w_to_o: \n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
	tmp.s0,
	tmp.s1,
	tmp.s2,
	tmp.s3,
	tmp.s4,
	tmp.s5,
	tmp.s6,
	tmp.s7,
	tmp.s8,
	tmp.s9,
	tmp.sA,
	tmp.sB,
	tmp.sC,
	tmp.sD,
	tmp.sE,
	tmp.sF);
*/
/*printf("scene.bg_color %#x | scene.camera.c_to_w %f %f %f %f - %f %f %f %f - %f %f %f %f - %f %f %f %f\n", scene->bg_color,
	scene->camera.c_to_w.s0,
	scene->camera.c_to_w.s1,
	scene->camera.c_to_w.s2,
	scene->camera.c_to_w.s3,
	scene->camera.c_to_w.s4,
	scene->camera.c_to_w.s5,
	scene->camera.c_to_w.s6,
	scene->camera.c_to_w.s7,
	scene->camera.c_to_w.s8,
	scene->camera.c_to_w.s9,
	scene->camera.c_to_w.sA,
	scene->camera.c_to_w.sB,
	scene->camera.c_to_w.sC,
	scene->camera.c_to_w.sD,
	scene->camera.c_to_w.sE,
	scene->camera.c_to_w.sF);
*/
//printf("scene1 %f  ", scene->camera.c_to_w.sF);
	float3 vcolor3 = get_pixel_color_from_mc_sampling(scene, random_seed, x_id, y_id);
//	printf((__constant char *)"kernel %f %f %f\n", vcolor3.x, vcolor3.y, vcolor3.z);
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
		//			__global		t_scene	*	scene,
					__local			uint *		random_seed
)
{
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;

	*random_seed = DEFAULT_SEED * work_item_id + DEFAULT_SEED;
//	float3 vcolor3 = rt_cl_f3rand_0_to_1(random_seed) * (float3)(255.);
//	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
//	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] = 0xFFFFFFFF;// color; /* simple interpolated colour gradient based on pixel coordinates */
}
