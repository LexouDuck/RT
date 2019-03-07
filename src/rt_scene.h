/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_SCENE_H
# define __RT_SCENE_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include "rt_cl.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define DEFAULT_CAM_POS			((cl_float3){{ 0., 0., 0. }})
# define DEFAULT_CAM_ANCHOR			((cl_float3){{ 0., 0., 0. }})
# define DEFAULT_CAM_TILT			0.
# define DEFAULT_CAM_FOV			0.4
# define DEFAULT_CAM_APERTURE		0.4
# define DEFAULT_CAM_FOCALDIST		0.02

# define DEFAULT_OBJECT_REFRAC		1.
# define DEFAULT_OBJECT_ROUGHNESS	0.0001
# define DEFAULT_OBJECT_OPACITY		1.

# define EPS						0.00003
# define DEFAULT_RENDER_DIST		100000.
# define DEFAULT_BG_COLOR			0xFF555555

# define OBJECT_ARGS_AMOUNT			14
# define OBJECT_NAME_MAXLENGTH		24
# define OBJECT_MAX_AMOUNT			32
# define DEFAULT_RAYSAMP_SIZE		64
# define DEFAULT_MAX_RAY_DEPTH		6

# define RENDER_MODES				5
# define DEFAULT_RENDER_MODE		4
typedef enum	e_rendermode
{
	RENDERMODE_MCPT = 0,
	RENDERMODE_BBOX_OS,
	RENDERMODE_BBOX_WS,
	RENDERMODE_SOLIDCOLOR,
	RENDERMODE_SOLIDTEXTURE,
}				t_rendermode;

# define CAMERA_MODELS	5
typedef enum	e_camera_model
{
	CAMERA_MODEL_PINHOLE = 0,
	CAMERA_MODEL_BLUR_SIMPLE,
	CAMERA_MODEL_BLUR_FOCAL,
	CAMERA_MODEL_AUTO_FOCUS,
	CAMERA_MODEL_ORTHOGRAPHIC
}				t_camera_model;

typedef enum	e_cameramode
{
	CAMERA_MODE_NONE = 0,
	CAMERA_MODE_ROTATE,
	CAMERA_MODE_TILT,
	CAMERA_MODE_PAN,
}				t_cameramode;

/*
** CAMERA
**
** world_pos	: cartesian coords of the camera in world space (world = anchor + pos)
** anchor		: cartesian coords of the anchor point around which this camera rotates and zooms
** pos			: cartesian coordinate of the camera's position relative to anchor
** zoom			: polar anchor-relative coord: how far from the anchor point is pos
** lat			: polar anchor-relative coord: horizontal angle of the camera
** lon			: polar anchor-relative coord: vertical angle of the camera
** tilt_angle	: the angle of tilting for this cam -> set to 0 for a regular upright cam
** tilt_vector	: the tilting vector for this cam: is {0, 1, 0} for a regular upright cam
** range_min	: the minimal amount of distance needed for an object to show on this cam
** range_max	: the maximum vision distance for this camera
** hrz_fov		: field-of-view horizontal angle in radians
** aperture		:
** w_to_c		: the camera's world-to-view/cam matrix
** c_to_w		: the camera's view/cam-to-world matrix (used to put rays in world space)
*/
typedef struct		s_camera
{
	t_cameramode	mode;
	cl_float3		world_pos;
	cl_float3		anchor;
	cl_float3		relative_pos;
	cl_float		zoom;
	cl_float		lat;
	cl_float		lon;
	cl_float		tilt_angle;
	cl_float3		tilt_vector;
	cl_float		range_min;
	cl_float		range_max;
	cl_float		hrz_fov;
	cl_float		aperture;
	cl_float		focal_dist;
	t_camera_model	model;
	cl_float16		c_to_w;
//	cl_float16		w_to_c;
}					t_camera;

/*
** c_to_w.s012 is axis_x, .s456 is axis_y, .s89A is axis_z and .sCDE is world_pos
*/

/*
**	camera.c
*/
void				init_camera(t_camera *camera);
void				camera_pan(t_camera *camera, float x, float y);
void				camera_rotate(t_camera *camera, float x, float y);
void				camera_zoom_tilt(t_camera *camera, float x, float y);
void				camera_update(t_camera *camera);

/*
**	cl_float3_util.c
*/
cl_float			cl_float3_norm(cl_float3 const *vector);
void				cl_float3_normalize(cl_float3 *vector);
cl_float			cl_float3_dot(cl_float3 *v1, cl_float3 *v2);
void				cl_float3_cross(cl_float3 *result, cl_float3 *v1, cl_float3 *v2);
char				*cl_float3_to_str(cl_float3 *vector, int i);

/*
**	init_scene.c
*/
void				init_scene(void);

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
	cl_float3		pos;
	cl_float3		dir;
	cl_float		t;
	cl_bool			complete;
	cl_int			hit_obj_id;
	cl_float3		hitpos;
//	cl_uint			depth;
	cl_float3		lum_mask;
	cl_float3		lum_acc;
	t_intersection	inter_type;
}					t_ray;

/*
** BVH: bounded volume hierarchies
** BBox: bounding box
*/
typedef struct		s_bbox
{
	cl_float3		vi;
	cl_float3		vf;
}					t_bbox;
/*
** typedef struct	s_bvh
** {
** 	cl_bst_node	*root;
** }				t_bvh;
*/

/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
# define			PRIMITIVES	14
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
	saddle,
	paraboloid,
	hyperboloid,
	infcylinder,
	infcone,
	obj_mesh,
}					t_primitive;

/*
** Categories for the optical properties of materials for each geometric
** primtive (ie, how they interact with or produce light). Normals play
** a major role here.
*/
# define			MATERIALS	4
typedef enum		e_material
{
// 	emits light
	light = 0,
// 	linear to-dark shading
	diffuse,
// 	returns a blended color of a reflection ray and a refraction ray
	transparent,
// 	has a special "lighter" mode of specular hightlighting
	specular,
// 	skybox ?
}					t_material;

# define			TEXTURE_PATTERNS	11
typedef	enum		e_pattern
{
	solid = 0,
	horizontal_wave,
	vertical_wave,
	wave,
	horizontal_stripe,
	vertical_stripe,
	checkerboard,
	hue,
	noise,
	marble,
	wood,
}					t_pattern;

# define			TEXTURE_PROJECTIONS	3
typedef	enum		e_uv_projection
{
	cubic = 0,
	spherical,
	cylindrical,
}					t_uv_projection;

typedef struct		s_texture
{
	t_pattern		pattern;
	cl_float		texel_value;
	cl_float3		uvw_pos;
	cl_float3		uvw_scale;
	cl_float3		bump_normal;
	cl_float3		rgb;
}					t_texture;

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
**					light emitted for a lightsource; albedo and filter for
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

typedef struct		s_object
{
	t_primitive		type;
	t_material		material;
	char			name[OBJECT_NAME_MAXLENGTH];
	cl_uint			color_a;
	cl_uint			color_b;
	cl_float3		rgb_a;
	cl_float3		rgb_b;
	cl_float3		pos;
	cl_float3		rot;
	cl_float3		scale;
	t_bbox			bbox_os;
	t_bbox			bbox_ws;
	cl_float		refrac;//refraction index for snell-descartes
	cl_float		roughness;
	cl_float		opacity;
	cl_float16		o_to_w;
	cl_float16		w_to_o;
	cl_float16		n_to_w;
	t_pattern		pattern;
	t_uv_projection	uv_projection;
}					t_object;

typedef struct		s_scene
{
	cl_uint			bg_color;
	cl_float3		bg_rgb;
	t_camera		camera;
	t_object		objects[OBJECT_MAX_AMOUNT];
	size_t			object_amount;
	cl_float		render_dist;
	t_bbox			bbox_ws;
	cl_uint			max_ray_depth;
	cl_uint			mc_raysamp_size;
	cl_uint			random_seed_time;
	t_rendermode	render_mode;
	size_t			work_dim[2];
}					t_scene;

#endif
