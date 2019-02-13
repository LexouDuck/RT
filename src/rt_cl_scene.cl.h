/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_scene.cl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_CL_SCENE_H
# define __RT_CL_SCENE_H

//# include "rt_cl.h"

# define BG_COLOR				0xFF00BB88 //0xFF000000

# define OBJ_MAX_AMOUNT			32
# define DEFAULT_RAYSAMP_SIZE	1024
# define DEFAULT_MAX_RAY_DEPTH	6

typedef enum		e_intersection
{
	INTER_INSIDE = -1,
	INTER_OUTSIDE = 1,
	INTER_NONE = 0
}					t_intersection;

/*
** CAMERA
**
** world_pos		: cartesian coordinate of camera in world
**						(world = anchor + relative)
** reltv_pos		: cartesian coordinate of camera with anchor as center
** polar_pos		: zoom/radius, longitude, latitude relative to anchor
** anchor			: origin of polar_pos and reltv_pos
** axis_x			: right vector of cam
** axis_y			: up vector of cam
** axis_z			: "forward" vector of cam,  input eye vector
** hrz_fov			: field-of-view horizontal angle in radians
** w_to_c			: the camera's world-to-view/cam matrix
** c_to_w			: the camera's view/cam-to-world matrix (useful to put
**						 rays in world space)
*/

typedef enum	e_cameramode
{
	CAMERA_NONE,
	CAMERA_ROTATE,
	CAMERA_TILT,
	CAMERA_PAN,
}				t_cameramode;
/*
** c_to_w.s012 is axis_x, .s456 is axis_y, .s89A is axis_z and .sCDE is world_pos
*/
typedef struct	s_camera
{
	float3		world_pos;
//	cl_float3		reltv_pos;
//	cl_float3		polar_pos;
	float3		anchor;
	float		tilt;
	float		hrz_fov;
	float		aperture;
	float16		c_to_w;
//	cl_float16		w_to_c;
	t_cameramode	mode;
}				t_camera;


/*
** RAYS
**
** Rays can be interpreted in any space, so beware.
** 			- "pos + scale(t, dir)" = "end of the current ray";
**			- t is init at MAX_RENDER_DIST.
**			- depth is the recursion depth of the ray being cast;
*/
typedef struct	s_ray
{
	float3	pos;
	float3	dir;
	float	t;
	bool	complete;
	int		hit_obj_id;
//	cl_uint		depth;
	float3	lum_acc;
}				t_ray;

/*
** BVH: bounded volume hierarchies
** BBox: bounding box
*/

typedef struct	s_bbox
{
	float3	vi;
	float3	vf;
}				t_bbox;
/*
typedef struct	s_bvh
{
	cl_bst_node	*root;
}				t_bvh;
*/

/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
typedef enum	e_primitive
{
	none = 0,
	plane,
	disk,
	rectangle,			
	cube,
	sphere,
	cylinder,
	cone,
//	infcylinder,
//	infcone,
//	paraboloid,
//	saddle,
	obj_mesh	
}				t_primitive;

/*
** Categories for the optical properties of materials for each geometric
** primtive (ie, how they interact with or produce light). Normals play
** a major role here.
*/
typedef enum	e_material
{
	lightsrc,
	diffuse,
//	mirror,
//	glassy,
//	glossy,
//	skybox ?
}				t_material;

/*
** This struct is used to translate, rotate and scale our object into position
**	in the world space.
**
** So that normals be calculated easily, rays are converted into object space
**	first, then compared with the basic primitive. The object_to_world matrix
**	is the succession of: scaling, then rotating, then translating, applied
**  to the basic primitive.
**
** type			: an enum to sort each geometric primitive, see above
** pos			: position in world space
** rot			: model angles of rotation (in radians) around (resp.)
**					the x-, y-, and z-axes
** scale		: (x, y, z) scaling factors as a vector (tmp diagonal matrix)
** rgb			: a vector of float from 0. to 1. representing how much each
**					object reflects each primary color of light,
**					respectively (r, g, b); albedo for a diffuse surface;
**					light emitted for a lightsrc; albedo and filter for
**					glassy, glossy and mirror surfaces.
** unit_w_to_o	: takes a unit vector from world space (that shouldn't be
**					translated) to a non-unit vector in object space
** unit_o_to_w	: takes a non-unit vector from object space (that shouldn't be
**					translated) to corresponding unit vector in world space
** o_to_w		: takes a vector that should be translated from object space
**					to world space
** w_to_o		: takes a vector that should be translated from world space
**					to object space
** n_to_w		: takes a vector that should be considered a normal of our
**					object from object space to world space, in practice,
**					normal_to_world = transpose(inverse(o_to_w))
** intersect	: the intersection function, set when type is set
** get_hnn		: the function that returns the appropriate hitpos and normal
**					of the ray on the object; note that the appropriate t
**					parameter should already be set before this function is
**					called
*/
/*
** Respective intensity for light source's rgb is vec3_scale(intensity, rgb),
**	where rgb contains values between 0. and 1.
*/

typedef struct	s_object
{
	t_primitive		type;
	t_material		material;
	float3		pos;
	float3		rot;
	float3		scale;
	uint			color; 
	float3		rgb;
	t_bbox			bbox;
//	cl_float3		specul;
//	t_float			refrac;//refraction index for snell-descartes
//	t_float			intensity;//intensity for lightsrc objects, 1. for other objects //or reflectivity ??
	float16		o_to_w;
	float16		w_to_o;
	float16		n_to_w;
}				t_object;

typedef struct	s_scene
{
	uint		bg_color;
	float3		bg_rgb;
	t_camera	camera;
	t_object	objects[OBJ_MAX_AMOUNT];
	ulong		object_amount;
	float		render_dist;
	t_bbox		bbox;
	uint		max_ray_depth;
	uint		mc_raysamp_size;
}				t_scene;




float16			rt_cl_mat44_transpose(float16 mat44);
float3			rt_cl_apply_linear_matrix(float16 mat44, float3 vec3);
float3			rt_cl_apply_homogeneous_matrix(float16 mat44, float3 vec3);
float16			rt_cl_build_diagonal_mat33in44(float3 diag);
float16			rt_cl_build_rotation_mat33in44(float theta, int axis);
float16			rt_cl_mat44_mul(float16 const mat_A, float16 const mat_B);
float			rt_cl_mat33in44_det(float16 const mat33);
float16			rt_cl_mat33in44_inv(float16 const mat33);
float16			rt_cl_build_cam_matrix(t_camera	camera);
void			rt_cl_build_object_matrices
(
				__global	t_object *	obj
);
void			rt_cl_get_vertices_for_bbox
(
							float3 *	vertices,
							t_bbox		aabb
);

t_bbox			rt_cl_build_object_bbox
(
							t_primitive		type,
							float16			o_to_w,
							float			render_dist
);




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

uint			rt_cl_rand
(
				__local		uint *	random_seed
);
uint			rt_cl_rand_0_to_pow2n
(
				__local 	uint *	random_seed,
							uint	n
);
uint			rt_cl_rand_0_to_n
(
				__local		uint *	random_seed,
							uint	n
);
int				rt_cl_rand_a_to_b
(
				__local		uint *	random_seed,
							int		a,
							int		b
);


float			rt_cl_frand_0_to_1
(
				__local		uint *	random_seed
);
float			rt_cl_frand_neg1half_to_pos1half
(
				__local		uint *	random_seed
);
float			rt_cl_frand_neg1_to_pos1
(
				__local		uint *	random_seed
);
float			rt_cl_frand_a_to_b
(
				__local		uint *	random_seed,
							float	a,
							float	b
);


float3			rt_cl_f3rand_0_to_1
(
				__local		uint *			random_seed	
);
float3			rt_cl_f3rand_neg1half_to_pos1half
(
				__local		uint *			random_seed	
);
float3			rt_cl_rand_dir_sphere
(
				__local		uint *			random_seed
);
/*
** Returns a random vector in a hemisphere defined by 'axis'.
** Axis should already be normalized when this function is called.
*/
float3			rt_cl_rand_dir_hemi
(
				__local		uint *			random_seed,
							float3 const	axis
);





# define INV_PI			0x1.45f306dc9c883p-2

bool			get_realroots_quadpoly
(
							float2 *	roots,
							float3		quadpoly
);
bool			ray_intersect_bbox
(
					t_ray		ray,
					t_bbox		aabb,
					float		tmin,
					float		tmax/*,
					float *		tres*/
);
t_intersection	ray_intersect_sphere
(
							float *		res,
							t_ray		ray
);
bool			trace_ray_to_scene
(
					__constant		t_scene	*	scene,
									t_ray *		ray
);
void			accumulate_lum_and_bounce_ray
(
									t_ray *		ray,
						__constant	t_scene	*	scene,
						__local		uint *		random_seed,
									int			depth		
);
float3			get_pixel_color_from_mc_sampling
(
					__constant		t_scene	*	scene,
					__local			uint *		random_seed,
									int			x_id,
									int			y_id
);


#endif