
# include "src/rt_cl_scene.cl.h"
//# include "src/rt_cl_build_scene.cl"







float16			rt_cl_mat44_transpose(float16 mat44)
{
	return (mat44.s048C159D26AE37BF);
}


void			debug_print_scene(__constant	t_scene *	scene)
{
	printf("\n\nScene:\n"
	"\tbg_color = %#x\n"
	"\tbg_rgb = %g %g %g\n"
	"\tobject_amount = %u\n"
	"\trender_dist = %10g\n"
	"\tbbox = %10g %10g %10g | %10g %10g %10g\n"
	"\tmax_ray_depth = %u\n"
	"\tmc_raysamp_size = %u\n",
	scene->bg_color,	
	scene->bg_rgb.x, scene->bg_rgb.y, scene->bg_rgb.z,
	scene->object_amount,
	scene->render_dist,
	scene->bbox.vi.x, scene->bbox.vi.y, scene->bbox.vi.z, scene->bbox.vf.x, scene->bbox.vf.y, scene->bbox.vf.z,
	scene->max_ray_depth,
	scene->mc_raysamp_size);
}


/*
** Use only the lines you need, memory is limited and you might get weird results
*/
void			debug_print_object(__global	t_object *	obj)
{
//	float16		ow;
	float16		wo;
//	float16		nw;


//	ow = rt_cl_mat44_transpose(obj->o_to_w);
	wo = rt_cl_mat44_transpose(obj->w_to_o);
//	nw = rt_cl_mat44_transpose(obj->n_to_w);
	printf("\n\nObject\n"
	//		"\tpos %g %g %g | scale %g %g %g | rot %g %g %g \n"
	//		"\tcolor %#08x | rgb %g %g %g\n"
			"\ttype %d | material %d | bbox %g %g %g    %g %g %g\n"
	//		"\tobj->o_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			"\tobj->w_to_o: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
	//		"\tobj->n_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n"
			,
	//obj->pos.x, obj->pos.y, obj->pos.z, obj->scale.x, obj->scale.y, obj->scale.z, obj->rot.x, obj->rot.y, obj->rot.z,
	//obj->color, obj->rgb.x, obj->rgb.y, obj->rgb.z,
	obj->type, obj->material, obj->bbox.vi.x, obj->bbox.vi.y, obj->bbox.vi.z, obj->bbox.vf.x, obj->bbox.vf.y, obj->bbox.vf.z,
//	ow.s0, ow.s1, ow.s2, ow.s3, ow.s4, ow.s5, ow.s6, ow.s7, ow.s8, ow.s9, ow.sA, ow.sB, ow.sC, ow.sD, ow.sE, ow.sF//,
	wo.s0, wo.s1, wo.s2, wo.s3, wo.s4, wo.s5, wo.s6, wo.s7, wo.s8, wo.s9, wo.sA, wo.sB, wo.sC, wo.sD, wo.sE, wo.sF//,
//	nw.s0, nw.s1, nw.s2, nw.s3, nw.s4, nw.s5, nw.s6, nw.s7, nw.s8, nw.s9, nw.sA, nw.sB, nw.sC, nw.sD, nw.sE, nw.sF
	);
}

void			debug_print_camera(__constant	t_camera *	camera)
{
	float16		c;

	c = rt_cl_mat44_transpose(camera->c_to_w);
	printf("\n\nCamera\n"
			"\tworld_pos %g %g %g | anchor %g %g %g\n"
			"\ttilt %g | hrz_fov %g | aperture %g"
			"\tc_to_w: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n",
		camera->world_pos.x, camera->world_pos.y, camera->world_pos.z, camera->anchor.x, camera->anchor.y, camera->anchor.z,
		camera->tilt, camera->hrz_fov, camera->aperture,
		c.s0, c.s1, c.s2, c.s3, c.s4, c.s5, c.s6, c.s7, c.s8, c.s9, c.sA, c.sB, c.sC, c.sD, c.sE, c.sF);
}

















/*

float16			rt_cl_mat44_transpose(float16 mat44)
{
	return (mat44.s048C159D26AE37BF);
}
*/

float3			rt_cl_apply_linear_matrix(float16 mat44, float3 vec3)
{
	float3		res;

	res.x = dot(mat44.s048, vec3);
	res.y = dot(mat44.s159, vec3);
	res.z = dot(mat44.s26A, vec3);
	return (res);
}


float3			rt_cl_apply_homogeneous_matrix(float16 mat44, float3 vec3)
{
	float4		tmp;
	float3		res;

	tmp.xyz = vec3;
	tmp.w = 1.;
	res.x = dot(mat44.s048C, tmp);
	res.y = dot(mat44.s159D, tmp);
	res.z = dot(mat44.s26AE, tmp);
	return (res);
}

float16			rt_cl_build_diagonal_mat33in44(float3 diag)
{
	float16		result = (float16)(0.);

	result.s05AF = (float4)(diag.x, diag.y, diag.z, 1.);
	return (result);
}

float16			rt_cl_build_rotation_mat33in44(float theta, int axis)
{
	float16		result;
	float		c_th;
	float		s_th;

	result = rt_cl_build_diagonal_mat33in44((float3)(1., 1., 1.));
	axis = axis % 3;
	s_th = sincos(theta, &c_th);
	if (axis == 0)
		result.s5A69 = (float4)(c_th, c_th, s_th, -s_th);
	else if (axis == 1)
		result.sA082 = (float4)(c_th, c_th, s_th, -s_th);
	else
		result.s0514 = (float4)(c_th, c_th, s_th, -s_th);
	return (result);
}

float16			rt_cl_mat44_mul(float16 const mat_A, float16 const mat_B)
{
	float16		mat_C;

	mat_C.s0 = dot(mat_A.s048C, mat_B.s0123);
	mat_C.s1 = dot(mat_A.s159D, mat_B.s0123);
	mat_C.s2 = dot(mat_A.s26AE, mat_B.s0123);
	mat_C.s3 = dot(mat_A.s37BF, mat_B.s0123);
	mat_C.s4 = dot(mat_A.s048C, mat_B.s4567);
	mat_C.s5 = dot(mat_A.s159D, mat_B.s4567);
	mat_C.s6 = dot(mat_A.s26AE, mat_B.s4567);
	mat_C.s7 = dot(mat_A.s37BF, mat_B.s4567);
	mat_C.s8 = dot(mat_A.s048C, mat_B.s89AB);
	mat_C.s9 = dot(mat_A.s159D, mat_B.s89AB);
	mat_C.sA = dot(mat_A.s26AE, mat_B.s89AB);
	mat_C.sB = dot(mat_A.s37BF, mat_B.s89AB);
	mat_C.sC = dot(mat_A.s048C, mat_B.sCDEF);
	mat_C.sD = dot(mat_A.s159D, mat_B.sCDEF);
	mat_C.sE = dot(mat_A.s26AE, mat_B.sCDEF);
	mat_C.sF = dot(mat_A.s37BF, mat_B.sCDEF);
	return (mat_C);
}


float			rt_cl_mat33in44_det(float16 const mat33in44)
{
	return (mat33in44.s0 * mat33in44.s5 * mat33in44.sA
			+ mat33in44.s1 * mat33in44.s6 * mat33in44.s8
			+ mat33in44.s2 * mat33in44.s4 * mat33in44.s9
			- mat33in44.s2 * mat33in44.s5 * mat33in44.s8
			- mat33in44.s1 * mat33in44.s4 * mat33in44.sA
			- mat33in44.s0 * mat33in44.s6 * mat33in44.s9);
}


/*
** M^-1 = 1/det * adj(m) and adj(m) = comat(m^transpose)
*/

float16			rt_cl_mat33in44_inv(float16 const mat33)
{
	float		det;
	float16		result;

	if ((det = rt_cl_mat33in44_det(mat33)) == 0.)
		return ((float16)(0. / 0.));
	result.s0 = mat33.s5 * mat33.sA - mat33.s6 * mat33.s9;
	result.s4 = mat33.s6 * mat33.s8 - mat33.s4 * mat33.sA;
	result.s8 = mat33.s4 * mat33.s9 - mat33.s5 * mat33.s8;
	result.s1 = mat33.s2 * mat33.s9 - mat33.s1 * mat33.sA;
	result.s5 = mat33.s0 * mat33.sA - mat33.s2 * mat33.s8;
	result.s9 = mat33.s1 * mat33.s8 - mat33.s0 * mat33.s9;
	result.s2 = mat33.s1 * mat33.s6 - mat33.s2 * mat33.s5;
	result.s6 = mat33.s2 * mat33.s4 - mat33.s0 * mat33.s6;
	result.sA = mat33.s0 * mat33.s5 - mat33.s1 * mat33.s4;
	result = (float16)(1. / det) * (result); //TODO use native_recip ?
	result.s37B = (float3)(0., 0., 0.);
	result.sCDEF = (float4)(0., 0., 0., 1.);                                                                                                                      
	return (result);
}






float16			rt_cl_build_cam_matrix
(
				t_camera	camera
)
{
	float16		cam_mat44 = (float16)(0.);
	float3		axis_x;
	float3		axis_y;
	float3		axis_z;
	float		sin_val;
	float		cos_val;

	sin_val = sincos(camera.tilt, &cos_val);
	axis_y = (float3)(sin_val, cos_val, 0.);
	axis_z = normalize(camera.world_pos - camera.anchor);
	axis_x = cross(axis_y, axis_z);
	axis_x = normalize(axis_x);
	axis_y = cross(axis_x, axis_z);

//TODO change here and/or in apply_matrix-s if row major is faster
	cam_mat44.s012 = axis_x;
	cam_mat44.s456 = axis_y;
	cam_mat44.s89A = axis_z;
	cam_mat44.sCDE = camera.world_pos;
	cam_mat44.sF = 1.;
	return (cam_mat44);
}




/*
** http://www.cs.nthu.edu.tw/~jang/book/addenda/matinv/matinv/
**
**	A homogeneous matrix is one with the last row equal to (0,0,0,1),
**	used to "linearize" the translation operation.
**
**	The page above give a neat formula to simplify our inverse calculation
**	when we choose the block C to be the last row's (0,0,0), D to be (1), etc.
**	To note, since C is null and D is (1), the inverse of the B block in a
**	homogeneous matrix is thus -inv(A)*B, and of the A block is simplu inv(A),
**	while C and D do not change.
**
**	Note that this also implies keeping a "linear" version of our 4*4 matrices
**	is unnecessary, as the corresponding linear_x_to_y matrix is always simply
**	the top left 3*3 block.
*/

void			rt_cl_build_object_matrices
(
					__global	t_object *	obj
)
{
	float3		pos = obj->pos;
	float3		scale = obj->scale;
	float3		rot = obj->rot;
	float16		rot_mat;
	float16		tmp_mat;

	rot_mat = rt_cl_build_rotation_mat33in44(rot.x, 0);
	tmp_mat = rt_cl_build_rotation_mat33in44(rot.y, 1);
	rot_mat = rt_cl_mat44_mul(tmp_mat, rot_mat);
	tmp_mat = rt_cl_build_rotation_mat33in44(rot.z, 2);
	rot_mat = rt_cl_mat44_mul(tmp_mat, rot_mat);
	tmp_mat = rt_cl_build_diagonal_mat33in44(scale);
	obj->o_to_w = rt_cl_mat44_mul(rot_mat, tmp_mat);
	obj->o_to_w.sCDE = pos;
	//the 3 lines for which there is a big comment above; could be made into a small 'invert homogeneous matrix' function
	tmp_mat = rt_cl_mat33in44_inv(obj->o_to_w);                                                                                                               
	obj->w_to_o = tmp_mat;
	obj->w_to_o.sCDE = rt_cl_apply_linear_matrix(tmp_mat, -pos); //note that this value is the corrected inverse translation considering scaling and rotation
	obj->n_to_w = rt_cl_mat44_transpose(tmp_mat);
}



void			rt_cl_get_vertices_for_bbox
(
					float3 *	vertices,
					t_bbox		aabb
)
{
	vertices[0] = (float3)(aabb.vi.x, aabb.vi.y, aabb.vi.z);
	vertices[1] = (float3)(aabb.vi.x, aabb.vi.y, aabb.vf.z);
	vertices[2] = (float3)(aabb.vi.x, aabb.vf.y, aabb.vi.z);
	vertices[3] = (float3)(aabb.vi.x, aabb.vf.y, aabb.vf.z);
	vertices[4] = (float3)(aabb.vf.x, aabb.vi.y, aabb.vi.z);
	vertices[5] = (float3)(aabb.vf.x, aabb.vi.y, aabb.vf.z);
	vertices[6] = (float3)(aabb.vf.x, aabb.vf.y, aabb.vi.z);
	vertices[7] = (float3)(aabb.vf.x, aabb.vf.y, aabb.vf.z);
}



t_bbox			rt_cl_build_object_bbox
(
							t_primitive		type,
							float16			o_to_w,
							float			render_dist
)
{
	t_bbox		objspace_bbox;
	float3		objspace_bbox_vertices[8];
	t_bbox		result;

	if (type == sphere || type == cube)
	{
		objspace_bbox = (t_bbox){(float3)(-1., -1., -1.),
									(float3)(1., 1., 1.)};
	}
	else
	{
		return ((t_bbox){(float3)(-render_dist, -render_dist, -render_dist),
							(float3)(render_dist, render_dist, render_dist)});
	}
	rt_cl_get_vertices_for_bbox(objspace_bbox_vertices, objspace_bbox);

	#pragma unroll
	for (int i = 0; i < 8; ++i)
	{
		objspace_bbox_vertices[i] = rt_cl_apply_homogeneous_matrix(o_to_w, objspace_bbox_vertices[i]);
	}

	result.vf = result.vi = objspace_bbox_vertices[0];
	#pragma unroll
	for (int i = 1; i < 8; ++i)
	{
		result.vi = fmin(result.vi, objspace_bbox_vertices[i]);
		result.vf = fmax(result.vf, objspace_bbox_vertices[i]);
	}

	return (result);
}





__kernel void	rt_cl_build_scene
(
					__global	t_scene	*	scene
)
{
				int const		obj_id = get_global_id(0);
	__global	t_object *		obj = &(scene->objects[obj_id]);

	scene->camera.c_to_w = rt_cl_build_cam_matrix(scene->camera);
	rt_cl_build_object_matrices(obj);
	obj->bbox = rt_cl_build_object_bbox(obj->type, obj->o_to_w, scene->render_dist);

debug_print_object(obj);
}





















/*
** ************************************************************************** *|
**                          Random Number Generator                           *|
** ************************************************************************** *|
*/

/*
** Random number generator. Modulus is 2^31
**
** - OFFSET and MODULUS are mutually prime.
** - CEIL_SQRT_MOD % 4 should be = 1 because MODULUS is a multiple of 4
** - For all P prime divisors of MODULUS, a % p = 1
** - OFFSET should be small compared to the two other parameters
** - The bitwise & is applied, which explains the choice of modulus to be
**		2^31 - 1 in implementation (could also be called RAND_MAX)
**
** Basic RNG formula is:
**		new_nb = (CEIL_SQRT_MOD  * old_nb + OFFSET) % MODULUS
*/




# define DEFAULT_SEED	0x93E21FD5

# define MODULUS		0x7FFFFFFF		
# define CEIL_SQRT_MOD	46341
# define OFFSET			2835

# define TAU 			0x1.921fb54442d18p2

# define INV_PI			0x1.45f306dc9c883p-2

static uint	rt_cl_rand_bit_shuffle
(
							uint	n
)
{
	uint	offset = n % 32;

	return ((n << (32 - offset)) ^ (n >> offset));
}


uint		rt_cl_rand
(
				__local		uint *	random_seed
)
{
	*random_seed = (CEIL_SQRT_MOD * rt_cl_rand_bit_shuffle(*random_seed) + OFFSET) & MODULUS;
	return (*random_seed);
}


uint		rt_cl_rand_0_to_pow2n
(
				__local 	uint *	random_seed,
							uint	n
)
{
	return (rt_cl_rand(random_seed) & ((0x1 << n) - 1));
}


uint		rt_cl_rand_0_to_n
(
				__local		uint *	random_seed,
							uint	n
)
{
	return (rt_cl_rand(random_seed) % n);
}


int			rt_cl_rand_a_to_b
(
				__local		uint *	random_seed,
							int		a,
							int		b
)
{
	int		res;

	res = (a < b) ?
		rt_cl_rand_0_to_n(random_seed, b - a) + a:
		rt_cl_rand_0_to_n(random_seed, a - b) + b;
	return (res);
}


float		rt_cl_frand_0_to_1
(
				__local		uint *	random_seed
)
{
	return ((float)rt_cl_rand(random_seed) / (float)MODULUS);
}

float		rt_cl_frand_neg1half_to_pos1half
(
				__local		uint *	random_seed
)
{
	return (rt_cl_frand_0_to_1(random_seed) - 1);
}

float		rt_cl_frand_neg1_to_pos1
(
				__local		uint *	random_seed
)
{
	return (2 * rt_cl_frand_neg1half_to_pos1half(random_seed));
}


float		rt_cl_frand_a_to_b
(
				__local		uint *	random_seed,
							float	a,
							float	b
)
{
	float	res = rt_cl_frand_0_to_1(random_seed);

	res *= (a < b) ?
		(b - a) + a:
		(a - b) + b;
	return (res);
}






float3			rt_cl_f3rand_0_to_1
(
				__local		uint *			random_seed	
)
{
	return (float3)(rt_cl_frand_0_to_1(random_seed),
					rt_cl_frand_0_to_1(random_seed),
					rt_cl_frand_0_to_1(random_seed));
}

float3			rt_cl_f3rand_neg1half_to_pos1half
(
				__local		uint *			random_seed	
)
{
	return (float3)(rt_cl_frand_0_to_1(random_seed) - 0.5,
					rt_cl_frand_0_to_1(random_seed) - 0.5,
					rt_cl_frand_0_to_1(random_seed) - 0.5);
}

//TODO add vectorial cos/phong sampling etc
//Add random points on algebraic curves

float3			rt_cl_rand_dir_sphere
(
				__local		uint *			random_seed
)
{
	float radius_cos_th = rt_cl_frand_neg1_to_pos1(random_seed); //rand_-1_to_1 = cos(theta)
    float radius_sin_th = sqrt(1 - radius_cos_th * radius_cos_th); // sin(theta)
    float lon = TAU * rt_cl_frand_0_to_1(random_seed);

    return (float3)(radius_cos_th, cos(lon) * radius_sin_th, sin(lon) * radius_sin_th);
}

/*
** Returns a random vector in a hemisphere defined by 'axis'.
** Axis should already be normalized when this function is called.
*/
float3			rt_cl_rand_dir_hemi
(
				__local		uint *			random_seed,
							float3 const	axis
)
{
	float3		randdir;
	float2		seed;
	float		tmp;
	float3		vtan1;
	float3		vtan2;
	float16		lin_mat;

	seed.x = TAU * rt_cl_frand_0_to_1(random_seed);
	seed.y = rt_cl_frand_0_to_1(random_seed);
	tmp = sqrt((float)(1. - seed.y * seed.y));
	randdir = (float3)(cos(seed.x) * tmp, sin(seed.x) * tmp, seed.y); //TODO convert to sincos ?
	vtan1 = rt_cl_f3rand_neg1half_to_pos1half(random_seed);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = rt_cl_apply_linear_matrix(lin_mat, randdir);
	return (randdir);
}






















/*
** ************************************************************************** *|
**	                        Intersection handling                             *|
** ************************************************************************** *|
*/


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


bool			trace_ray_to_scene
(
					__constant		t_scene	*	scene,
									t_ray *		ray,
									uint		depth
)
{
	bool			inter;
	float			new_t;
	t_ray			ray_os;
	t_ray			new_ray;

	inter = false;
	for (uint i = 0; i < scene->object_amount; ++i)
	{
		if (ray_intersect_bbox(*ray, scene->objects[i].bbox, 0, ray->t))
		{
			ray_os = *ray;
			ray_os.pos = rt_cl_apply_homogeneous_matrix(scene->objects[i].w_to_o, ray_os.pos);
			ray_os.dir = rt_cl_apply_linear_matrix(scene->objects[i].w_to_o, ray_os.dir);//DO NOT NORMALIZE: YOU NEED TO KEEP ray.t CONSISTENT
			if (ray_intersect_sphere(&new_t, ray_os))
			{	
				inter = true;
				new_ray = ray_os;
				new_ray.hit_obj_id = i;
				ray->t = new_t;
				new_ray.t = new_t;
			}
		}
	}
	if (inter)
		*ray = new_ray;
	return (inter);
}


void			accumulate_lum_and_bounce_ray
(
									t_ray *		ray,
						__constant	t_scene	*	scene,
						__local		uint *		random_seed//,
						//			int			depth		
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

	ray->lum_mask *= obj->rgb;// * (float3)(depth > 0 ? 1. : 1. / (ray->t * ray->t));
	if (obj->material == lightsrc)
	{
		ray->complete = true;
		return ;
	}
	else
	{
		hitpos = ray->pos + ((float3)ray->t) * ray->dir;
		new_ray.pos = rt_cl_apply_homogeneous_matrix(obj->o_to_w, hitpos);
		normal = normalize(rt_cl_apply_linear_matrix(obj->n_to_w, hitpos)); //sphere formula, normal == hitpos
//		new_ray.dir = rt_cl_rand_dir_hemi(random_seed, normal);
//		new_ray.dir = normalize(rt_cl_f3rand_neg1half_to_pos1half(random_seed));
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
	int const			width = get_global_size(0);
	int const			height = get_global_size(1);
	float3			res_pixel_color = (float3)(0.);
	float16	const	cam_mat44 = scene->camera.c_to_w;
	float const		fov_val = -width / (2 * tan(scene->camera.hrz_fov));
//	float3			cur_color;
	t_ray			ray_i;

//printf("scene2 %10g  ", scene->camera.c_to_w.sF);
	for (uint i = 0; i < scene->mc_raysamp_size; ++i)
	{
		random_seed = DEFAULT_SEED + random_seed + x_id + y_id;// + i;
		ray_i.t = scene->render_dist;
		ray_i.complete = false;
		ray_i.hit_obj_id = -1;
		ray_i.pos = scene->camera.world_pos;
/*		ray_i.pos = (float3(0., 0., 0.);
		ray_i.pos += rt_cl_f3rand_0_to_1(random_seed) - (float3)(0.005, 0.005, 0.); //add and fix with camera.aperture for depth of field
		ray_i.pos = rt_cl_apply_homogeneous_matrix(cam_mat44, ray_i.pos);
*/		ray_i.dir = (float3)(x_id - width / 2, y_id - height / 2, fov_val);
/*		ray_i.dir += rt_cl_f3rand_0_to_1(random_seed) - (float3)(0.005, 0.005, 0.); //add and fix for anti-aliasing
*/		ray_i.dir = rt_cl_apply_linear_matrix(cam_mat44, ray_i.dir);
		ray_i.dir = normalize(ray_i.dir);
		ray_i.lum_mask = (float3)(1.);
//		printf("pos: %g %g %g | dir: %g %g %g | t: %g\n", ray_i.pos.x, ray_i.pos.y, ray_i.pos.z, ray_i.dir.x, ray_i.dir.y, ray_i.dir.z, ray_i.t);
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
*/
//		for (uint depth = 0; depth < scene->max_ray_depth; ++depth)
//		{
		//	trace_ray_to_bboxes(ray, scene);
		//	trace_ray_to_primitives(ray, scene, index_list);
			if (trace_ray_to_scene(scene, &ray_i, 0))
			{
//				return scene->objects[ray_i.hit_obj_id].rgb;
				accumulate_lum_and_bounce_ray(&ray_i, scene, random_seed);
			}			
//printf("hit_obj = %d | depth = %d\n", ray_i.hit_obj_id);
			else
			{
//				return (0xFF000000);
				ray_i.complete = true;
				ray_i.lum_mask = ray_i.lum_mask * scene->bg_rgb;
				break;
			}
//		}
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
	int const			width = get_global_size(0);
	int const			height = get_global_size(1);
	int const			x_id = get_global_id(0); /* x-coordinate of the current pixel */
	int const			y_id = get_global_id(1); /* y-coordinate of the current pixel */
//	int const			sample_id = get_global_id(2); /* id of the current ray thread amongst the MC simulation for the current pixel*/
	int const			work_item_id = y_id * get_global_size(0) + x_id;


//if (x_id == 0 && y_id == 0) {debug_print_scene(scene); debug_print_camera(&(scene->camera));} printf("sizes %u in %u and %u in %u \n", x_id, width, y_id, height);
//printf("scene1 %10g  ", scene->camera.c_to_w.sF);
	float3 vcolor3 = get_pixel_color_from_mc_sampling(scene, random_seed, x_id, y_id);
//	printf((__constant char *)"kernel %10g %10g %10g\n", vcolor3.x, vcolor3.y, vcolor3.z);
	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] = color; /* simple interpolated colour gradient based on pixel coordinates */
}

























#if 0
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

	*random_seed = DEFAULT_SEED * work_item_id + DEFAULT_SEED;
	float3 vcolor3 = rt_cl_f3rand_0_to_1(random_seed) * (float3)(255.);
	uint3 color3 = (uint3)(floor(vcolor3.x), floor(vcolor3.y), floor(vcolor3.z));
//	printf((__constant char *)"kernel %u %u %u\n", color3.x, color3.y, color3.z);
	uint color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
//	printf("kernel %x %x %x color %x\n", (color3.x << 16), (color3.y << 8), (color3.z), color);
	result_imgbuf[work_item_id] =  color; /* simple interpolated colour gradient based on pixel coordinates */


#if 0
if (x_id == 0 && y_id == 0)
{

	__constant t_object *	obj = &(scene->objects[0]);
//printf((__constant char *)"pos : %10g %10g %10g | scale %10g %10g %10g | rot %10g %10g %10g \n", obj->pos.x, obj->pos.y, obj->pos.z, obj->scale.x, obj->scale.y, obj->scale.z, obj->rot.x, obj->rot.y, obj->rot.z);

float16 tmp = rt_cl_mat44_transpose(obj->w_to_o);
printf("obj->w_to_o: \n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n%10g %10g %10g %10g\n",
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

}
#endif
}
#endif