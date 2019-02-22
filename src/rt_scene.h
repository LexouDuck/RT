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

# define DEFAULT_CAM_POS		((cl_float3){{ 3., 6.,-5. }})
# define DEFAULT_CAM_ANCHOR		((cl_float3){{ 0., 0., 0. }})
# define DEFAULT_CAM_TILT		0.
# define DEFAULT_CAM_FOV		0.8
# define DEFAULT_CAM_APERTURE	0.05

# define DEFAULT_RENDER_DIST	100000.
# define EPS					0.001

# define BG_COLOR				0xFF00BB88 //0xFF000000

# define OBJECT_NAME_MAXLENGTH	24
# define OBJECT_MAX_AMOUNT		32
# define DEFAULT_RAYSAMP_SIZE	128
# define DEFAULT_MAX_RAY_DEPTH	4

typedef enum		e_intersection
{
	INTER_INSIDE = -1,
	INTER_OUTSIDE = 1,
	INTER_NONE = 0
}					t_intersection;

typedef enum	e_cameramode
{
	CAMERA_MODE_NONE,
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
typedef struct	s_camera
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
	cl_float16		c_to_w;
//	cl_float16		w_to_c;
	cl_uint2		target_pos;
	cl_uint			target_id;
}				t_camera;
/*
** c_to_w.s012 is axis_x, .s456 is axis_y, .s89A is axis_z and .sCDE is world_pos
*/

/*
**	camera.c
*/
void		init_camera(t_camera *camera);
void		camera_pan(t_camera *camera, float x, float y);
void		camera_rotate(t_camera *camera, float x, float y);
void		camera_zoom_tilt(t_camera *camera, float x, float y);
void		camera_update(t_camera *camera);
/*
**	cl_float3_util.c
*/
cl_float	cl_float3_norm(cl_float3 const *vector);
void		cl_float3_normalize(cl_float3 *vector);
cl_float	cl_float3_dot(cl_float3 *v1, cl_float3 *v2);
void		cl_float3_cross(cl_float3 *result, cl_float3 *v1, cl_float3 *v2);
char		*cl_float3_to_str(cl_float3 *vector, int i);
/*
**	init_scene.c
*/
void		init_scene(void);

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
	cl_float3		pos;
	cl_float3		dir;
	cl_float		t;
	cl_bool			complete;
	cl_int			hit_obj_id;
//	cl_uint			depth;
	cl_float3		lum_mask;
	cl_float3		lum_acc;
	t_intersection	inter_type;
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
//HUGO
	infcylinder,
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
	lightsrc = 0,	// simply returns object->color
	diffuse,		// linear to-dark shading
//	light,			// this material emits light
//	mirror,			// returns a reflection ray color
//	glass,			// returns a blended color of a reflection ray and a refraction ray
//	glossy,			// has a special "lighter" mode of specular hightlighting
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
	char			name[OBJECT_NAME_MAXLENGTH];
	cl_float3		pos;
	cl_float3		rot;
	cl_float3		scale;
	cl_uint			color;
	cl_float3		rgb;
	cl_float3		light;
	t_bbox			bbox;
//	cl_float3		specul;
//	t_float			refrac;//refraction index for snell-descartes
//	t_float			intensity;//intensity for lightsrc objects, 1. for other objects //or reflectivity ??
	cl_float16		o_to_w;
	cl_float16		w_to_o;
	cl_float16		n_to_w;
}				t_object;

typedef struct	s_scene
{
	cl_uint		bg_color;
	cl_float3	bg_rgb;
	t_camera	camera;
	t_object	objects[OBJECT_MAX_AMOUNT];
	size_t		object_amount;
	cl_float	render_dist;
	t_bbox		bbox;
	cl_uint		max_ray_depth;
	cl_uint		mc_raysamp_size;
	cl_uint		random_seed_time;
}				t_scene;

#endif
