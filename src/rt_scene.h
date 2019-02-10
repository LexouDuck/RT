#ifndef __RT_SCENE_H
# define __RT_SCENE_H

# define BG_COLOR				0xFF00BB88 //0xFF000000

# define MAX_OBJ_NB				32
# define DEFAULT_RAYSAMP_SIZE	1024

typedef enum		e_intersection
{
	INTER_INSIDE = -1;
	INTER_OUTSIDE = 1;
	INTER_NONE = 0;
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

typedef struct	s_camera
{
	cl_float3		world_pos;
//	cl_float3		reltv_pos;
//	cl_float3		polar_pos;
	cl_float3		anchor;
//	cl_float3		axis_x;
//	cl_float3		axis_y;
//	cl_float3		axis_z;
	cl_float		tilt;
	cl_float		hrz_fov;
	cl_float		aperture;
//	cl_float16		c_to_w;
//	cl_float16		w_to_c;
//	t_mat_3b3		linear_c_to_w;
//	t_mat_3b3		linear_w_to_c;
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
	cl_float3	pos;
	cl_float3	dir;
	cl_float	t;
	cl_bool		complete;
	cl_int		hit_obj_id;
//	cl_uint		depth;
	cl_float3	lum_acc;
}				t_ray;

/*
** BVH: bounded volume hierarchies
** BBox: bounding box
*/

typedef struct	s_bbox
{
	cl_float3	vi;
	cl_float3	vf;
}				t_bbox;
/*
typedef struct	s_bvh
{
	cl_bst_node	*root;
}				t_bvh;

/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
typedef enum	e_primitive
{
	null_obj,			//0
	sphere//,				//1
//	plane,				//2
//	disk,
//	square,
//	triangle,			//5
//	infcylinder,
//	cylinder,
//	infcone,
//	cone,
//	cube,				//10
//	paraboloid,
//	saddle,
//	obj_mesh	
}				t_primitive;

/*
** Categories for the optical properties of materials for each geometric
** primtive (ie, how they interact with or produce light). Normals play
** a major role here.
*/
typedef enum	e_material
{
	lightsrc,
	diffuse/*,
	mirror,
	glassy,
	glossy*/
	/*,
	skybox ?*/
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
	cl_float3		pos;
	cl_float3		rot;
	cl_float3		scale; 
	cl_float3		rgb;
	t_bbox			bbox;
//	cl_float3		specul;
//	t_float			refrac;//refraction index for snell-descartes
//	t_float			intensity;//intensity for lightsrc objects, 1. for other objects //or reflectivity ??
//	t_mat_4b4		o_to_w;
//	t_mat_4b4		w_to_o;
//	t_mat_3b3		linear_o_to_w;
//	t_mat_3b3		linear_w_to_o;
//	t_mat_3b3		n_to_w;
}				t_object;

typedef struct	s_scene
{
	t_camera	camera;
	t_object	objects[MAX_OBJ_NB];
	cl_int		object_array_len;
	cl_float	render_dist;
	cl_int		max_ray_depth;
	cl_int		mc_raysamp_size;
}				t_scene;

#endif