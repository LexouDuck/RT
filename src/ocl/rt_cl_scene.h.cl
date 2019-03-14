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

# define OBJECT_NAME_MAXLENGTH	24
# define OBJECT_MAX_AMOUNT		32
# define EPS					0.001

/*
** # define HALF_PI		0x1.921fb54442d18p0
** # define PI			0x1.921fb54442d18p1
** # define TAU 		0x1.921fb54442d18p2
** # define INV_PI		0x1.45f306dc9c883p-2
** # define INV_TAU		0x1.45f306dc9c883p-3
*/

# define PI						0x1.921fb54442d18p1f
# define TAU 					0x1.921fb54442d18p2f
# define TWOTAU					0x1.921fb54442d18p3f
# define INV_PI					0x1.45f306dc9c883p-2f
# define INV_TAU				0x1.45f306dc9c883p-3f

typedef enum		e_rendermode
{
	RENDERMODE_MCPT = 0,
	RENDERMODE_BBOX_OS,
	RENDERMODE_BBOX_WS,
	RENDERMODE_SOLIDCOLOR,
	RENDERMODE_SOLIDTEXTURE,
	RENDERMODE_NORMALS,
}					t_rendermode;

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
typedef enum		e_camera_model
{
	CAMERA_MODEL_PINHOLE = 0,
	CAMERA_MODEL_BLUR_SIMPLE,
	CAMERA_MODEL_BLUR_FOCAL,
	CAMERA_MODEL_AUTO_FOCUS,
	CAMERA_MODEL_ORTHOGRAPHIC
}					t_camera_model;

typedef enum		e_cameramode
{
	CAMERA_MODE_NONE = 0,
	CAMERA_MODE_ROTATE,
	CAMERA_MODE_TILT,
	CAMERA_MODE_PAN,
}					t_cameramode;

/*
** c_to_w.s012 is axis_x, .s456 is axis_y, .s89A is axis_z and .sCDE is world_pos
*/

typedef struct		s_camera
{
	t_cameramode	mode;
	float3			world_pos;
	float3			anchor;
	float3			relative_pos;
	float			zoom;
	float			lat;
	float			lon;
	float			tilt_angle;
	float3			tilt_vector;
	float			range_min;
	float			range_max;
	float			hrz_fov;
	float			aperture;
	float			focal_dist;
	float3			rgb_shade;
	float3			rgb_mask;
	t_camera_model	model;
	float16			c_to_w;
}					t_camera;

/*
** RAYS
**
** Rays can be interpreted in any space, so beware.
** 			- "pos + scale(t, dir)" = "end of the current ray";
**			- t is init at MAX_RENDER_DIST.
**			- depth is the recursion depth of the ray being cast;
*/
typedef enum		e_intersection
{
	INTER_INSIDE = -1,
	INTER_OUTSIDE = 1,
	INTER_NONE = 0
}					t_intersection;

typedef struct		s_ray
{
	float3			pos;
	float3			dir;
	float			t;
	int				hit_obj_id;
	float3			hitpos;
	float3			lum_mask;
	float3			lum_acc;
	float			refrac;
	t_intersection	inter_type;
	bool			complete;
}					t_ray;

/*
** BVH: bounded volume hierarchies
** BBox: bounding box
*/

typedef struct		s_bbox
{
	float3	vi;
	float3	vf;
}					t_bbox;

/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
typedef enum		e_primitive
{
	none = 0,
	sphere,
	cube,
	cylinder,
	cone,
	plane,
	rectangle,
	disk,
	triangle,
	paraboloid,
	hyperboloid,
	infcylinder,
	infcone,
	saddle,
	obj_mesh,
}					t_primitive;

/*
** Categories for the optical properties of materials for each geometric
** primtive (ie, how they interact with or produce light). Normals play
** a major role here.
*/
typedef enum		e_material
{
	light = 0,
	diffuse,
	transparent,
	specular,
}					t_material;

typedef	enum		e_pattern
{
	solid = 0,
	horizontal_wave,
	vertical_wave,
	double_wave,
	horizontal_stripe,
	vertical_stripe,
	checkerboard,
	image,
	perlin,
	marble,
	wood,
}					t_pattern;

typedef	enum		e_bump
{
	flat = 0,
	bump,
}					t_bump;

typedef struct		s_texture
{
	t_pattern		pattern;
	float			texel_value;
	float3			uvw_pos;
	float3			uvw_scale;
	float3			uvw_offset;
	t_bump			bump_type;
	float3			bump_normal;
	float3			rgb;
}					t_texture;

typedef	enum		e_projection
{
	spherical = 0,
	cubic,
	cylindrical,
}					t_projection;

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
	t_primitive			type;
	t_material			material;
	char				name[OBJECT_NAME_MAXLENGTH];
	uint				color_a;
	uint				color_b;
	float3				rgb_a;
	float3				rgb_b;
	float3				pos;
	float3				rot;
	float3				scale;
	t_bbox				bbox_os;
	t_bbox				bbox_ws;
	float3				uvw_scale;
	float3				uvw_offset;
	float				refrac;//refraction index for snell-descartes
	float				roughness;
	float				opacity;
	float16				o_to_w;
	float16				w_to_o;
	float16				n_to_w;
	t_pattern			pattern;
	t_projection		uvw_projection;
	t_bump				bump_type;
}				t_object;

typedef struct	s_work_array
{
	size_t			x;
	size_t			y;
	size_t			z;
}				t_work_array;

typedef struct		s_scene
{
	uint			bg_color;
	float3			bg_rgb;
	t_camera		camera;
	t_object		objects[OBJECT_MAX_AMOUNT];
	size_t			object_amount;
	float			render_dist;
	t_bbox			bbox_ws;
	uint			max_ray_depth;
	uint			mc_raysamp_size;
	uint			random_seed_time;
	t_rendermode	render_mode;
	t_work_array	work_dims;
	t_work_array	work_steps;
}				t_scene;
