/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:34:32 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/25 02:30:39 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H


//TODO add to math.h
#define INV_TAU		0x1.45f306dc9c88p-3


/*
 TODO:

 -Fix object / light dichotomy so that objects may act as secondary light
 sources and light source can be other things than punctual (long)
 -Break up shader.c in order to return color vectors rather than t_color
 -Fill the different color vector layers then write a merge function
*/

/*
** NB : convention used is +x for right axis, +y for up axis, +z for back axis
*/

# include "../libft/hdr/libft.h"
# include "../libft/hdr/libft_algebra.h"
# include "../libft/hdr/ft_printf.h"
# include "../libft/hdr/get_next_line.h"
# include "mlx_event_mac.h"
# include "ft_random.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>

# define REN_W		360
# define REN_H		270
# define PIXEL_NB	REN_W * REN_H

# define BLACK					0x000000
# define RED					0xFF0000
# define GREEN					0x00FF00
# define BLUE					0x0000FF
# define WHITE					0xFFFFFF
# define DBG_COLOR				0x5500BB
# define MIRROR_DBG_COLOR		0x11BB33
# define BG_COLOR				0x00BB88
# define MIRROR_DAMPEN_COLOR	0xDDEEDD
# define GLASSY_DAMPEN_COLOR	0xDDDDEE
# define INV_MAX_COLOR			(1. / 255.)

# define APPROX					0.000001

# define INIT_FOV				0.8

# define MAX_FILE_LN_NB			1024
# define MAX_LGT_NB				16
# define MAX_OBJ_NB				32

# define MAX_RAY_DEPTH			7 //4
# define MAX_SAMPRAY_DEPTH		0 //3
# define RAY_SAMPLE_NB			32//16//32 //8
# define INV_RAY_SAMPLE_NB		(1. / RAY_SAMPLE_NB)//0.0625//0.003125//0.125

typedef struct	s_point
{
	t_s32		x;
	t_s32		y;
}				t_point;

typedef t_u32		t_color;

typedef struct		s_rgb
{	
	t_float		r;
	t_float		g;
	t_float		b;
}					t_rgb;

typedef union		u_vcolor
{
	t_rgb		val;
	t_vec_3d	vec;
}					t_vcolor;

typedef struct	s_image_buffer
{
	t_vcolor	img[PIXEL_NB];
}				t_image_buffer;

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
typedef struct	s_camera
{
	t_vec_3d		world_pos;
	t_vec_3d		reltv_pos;
	t_vec_3d		polar_pos;
	t_vec_3d		anchor;
	t_vec_3d		axis_x;
	t_vec_3d		axis_y;
	t_vec_3d		axis_z;
	t_float			hrz_fov;
	t_mat_4b4		c_to_w;
	t_mat_4b4		w_to_c;
	t_mat_3b3		linear_c_to_w;
	t_mat_3b3		linear_w_to_c;
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
	t_vec_3d	pos;
	t_vec_3d	dir;
	t_float		t;
	t_u8		depth;
	t_u8		sray_depth;
}				t_ray;

/*
** Monte Carlo sample over which each pixel's color is averaged over
** a set number of rays.
*/
typedef struct	s_ray_sample
{
	t_ray		rays[RAY_SAMPLE_NB];
	t_float		probs[RAY_SAMPLE_NB];
	t_vcolor	lum[RAY_SAMPLE_NB];
//	t_vcolor	diff;
//	t_vcolor	spec;
//	t_vcolor	glob;
//	t_u32		pixel;//index in img buf
}				t_ray_sample;

/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
typedef enum	e_objtype
{
	null_obj,			//0
	sphere,				//1
	plane,				//2
	disk,
	square,
	triangle,			//5
	infcylinder,
	cylinder,
	infcone,
	cone,
	cube,				//10
	paraboloid,
	saddle
}				t_objtype;

/*
** Categories for the optical properties of materials for each geometric
** primtive (ie, how they interact with or produce light). Normals play
** a major role here.
*/
typedef enum	e_material
{
	lightsrc,
	diffuse,
	mirror,
	glassy,
	glossy
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
** scl			: (x, y, z) scaling factors as a vector (tmp diagonal matrix)
** rot			: model angles of rotation (in radians) around (resp.)
**					the x-, y-, and z-axes
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
typedef t_bool	(*t_inter_func)(t_ray *objray);
typedef void	(*t_hnn_func)(t_vec_3d hp, t_vec_3d nml, t_ray const objr);

typedef struct	s_object
{
	t_objtype		type;
	t_material		material;
	t_vec_3d		pos;
	t_vec_3d		scl;
	t_vec_3d		rot;
	t_vcolor		rgb;
	t_vec_3d		specul;
	t_float			refrac;//refraction index for snell-descartes
	t_float			intensity;//intensity for lightsrc objects, 1. for other objects //or reflectivity ??
	t_mat_4b4		o_to_w;
	t_mat_4b4		w_to_o;
	t_mat_3b3		linear_o_to_w;
	t_mat_3b3		linear_w_to_o;
	t_mat_3b3		n_to_w;
	t_inter_func	intersect;
	t_hnn_func		get_hnn;
}				t_object;

/*
** SHADERS
**
** The shader struct contains the absolute information concerning the
** reflection/refraction/diffusion problem at the intersection point.
**
** When building a shader, remember to pass the outgoing ray into
** world space before handing it to the next tracer.
*/
typedef struct	s_shader
{
	t_ray		in_ray;//incident ray in object space coordinates
	t_ray		out_ray_os;
	t_ray		out_ray_ws;
	//towards light objects (direct lighting); we choose the point on the surface randomly with a bias towards the nearest point on the object
	//towards normal (non spotlst) objects (indirect lighting), it is created with a cos hemisphere sampling for diffuse and phong lobe sampling for glossy surfaces
	t_vec_3d	normal_os; //the normal of the incident ray to the object.
	t_vec_3d	normal_ws;
	t_object	*hit_obj;
	//TODO previous object, or better, previous shader, kept for specular ?
}				t_shader;


/*
** SOFTWARE CONTROL TABLE
*/
typedef struct	s_control
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				img_bpp;
	int				img_bpl;
	int				img_bytelen;
	int				endian;
	char			*img_data;
//	t_image_buffer	*layers; //direct diffuse, specular, indirect diffuse (path-tracing, ambient), sum
	t_camera		cam;
	t_float			render_dist;
	t_bool			debug;
	t_bool			show_diffuse;
	t_bool			show_specular;
	t_bool			show_ambient;
	t_point			mouse;
	t_object		objlst[MAX_OBJ_NB];
	int				objlst_len;
	t_object		spotlst[MAX_LGT_NB];
	int				spotlst_len;
}				t_control;

void			exit_error(char *e_msg, int e_no);


/*
** vec3_utils.c
*/
void			vec3_schur(t_vec_3d res,
								t_vec_3d const v1,
								t_vec_3d const v2);
void			vec3_displace(t_vec_3d edit,
									t_float const coef,
									t_vec_3d const dir);
void			mat44_app_vec3(t_vec_3d result,
									t_mat_4b4 const mat,
									t_vec_3d const v);

/*
** image_utils.c
*/
int				point_in_bounds(int x, int y);
void			mlximg_setpixel(t_control *ctrl, int color, int x, int y);
void			mlximg_fill(t_control *ctrl, t_u32 val);
void			mlximg_clear(t_control *ctrl);

/*
** reader.c
*/
void			read_rt_file(t_control *ctrl, char const *fpath);

/*
** reader_utils.c
**
** static void			r_rt_f_read_vec3_line(t_vec_3d res, int fd);
*/
void			r_rt_f_setup_light(t_control *ctrl, int fd);
void			r_rt_f_set_obj(t_control *ctrl, int fd, t_objtype type);
void			r_rt_f_set_cam(t_control *ctrl, int fd);

/*
** camera.c
**
** static void		build_cam_matrices(t_mat_4b4 result, t_camera const cam);
*/
t_camera		init_cam(t_vec_3d polar_cam_pos, t_vec_3d anchor,
							t_float hrz_fov);

/*
** render.c
*/
int				handle_redraw(void *param);
void			render(t_control *ctrl);

/*
** coordinates.c
*/
void			vec3_polar_to_cartesian(t_vec_3d result, t_vec_3d const src);
void			vec3_cartesian_to_polar(t_vec_3d result, t_vec_3d const src);

/*
** event_key.c
*/
int				handle_key(int key, void *param);

/*
** rays.c
** TODO move ray_handlers
*/
t_vcolor		resolve_intersection(t_control *ctrl,
							t_shader oldshdr,
							t_object *hit_obj,
							t_ray const incident);
void			cast_rays(t_control *ctrl);

/*
** ray_utils.c
*/
t_ray			ray_x_to_y(t_mat_4b4 const x_to_y,
						t_mat_3b3 const linear_x_to_y,
						t_ray const ray);
void			get_ray_hitpos(t_vec_3d hitpos, t_ray const objray);
void			get_reflect(t_vec_3d res_reflected_dir,
							t_vec_3d const incident_dir,
							t_vec_3d const normal);
void			shader_get_reflect(t_shader *shdr);
t_bool			shader_get_transmit(t_shader *shdr);


/*
** tracers.c
*/
t_bool			trace_ray_to_objs(t_control *ctrl, t_ray ray,
									t_object **hit_obj, t_ray *res_objray);
t_bool			trace_ray_to_spots(t_control *ctrl, t_ray ray,
									t_object **hit_spot, t_ray *res_lgtray);
t_vcolor		trace_ray_to_scene(t_control *ctrl, t_shader shdr);


/*
** objects.c
*/
void			build_obj(t_object *obj, t_objtype type, t_material material);

/*
** shader.c
*/
t_vcolor		get_lum_from_lightsrc(
								t_shader const objshdr,
								t_shader const lgtshdr);
t_color			vcolor_to_color(t_vcolor const lum);
t_vcolor		color_to_vcolor(t_color const clr);


/*
** samplers.c
*/
t_ray_sample	ray_sample_init_w_fixed_origin(
							t_ray const fxd_pos,
							t_vec_3d const axis,
							t_u32 const phong);

/*
** primitive_utils.c
*/
t_bool			get_realroots_quadpoly(t_float *root1, t_float *root2,
									t_vec_3d const quadpoly);
void			print_object(t_object const obj);

/*
** primitives_2d.c
*/
t_bool			intersect_ray_plane(t_ray *objray);
t_bool			intersect_ray_disk(t_ray *objray);
t_bool			intersect_ray_square(t_ray *objray);
t_bool			intersect_ray_triangle(t_ray *objray);
void			get_hnn_plane(t_vec_3d hitpos, t_vec_3d normal,
							t_ray const objray);

/*
** sphere.c
*/
t_bool			intersect_ray_sphere(t_ray *objray);
void			get_hnn_sphere(t_vec_3d hitpos, t_vec_3d normal,
								t_ray const objray);

/*
** cone.c
*/
t_bool			intersect_ray_infcone(t_ray *objray);
void			get_hnn_infcone(t_vec_3d hitpos, t_vec_3d normal,
								t_ray const objray);
t_bool			intersect_ray_cone(t_ray *objray);
void			get_hnn_cone(t_vec_3d hitpos, t_vec_3d normal,
								t_ray const objray);
/*
** cylinder.c
*/
t_bool			intersect_ray_infcylinder(t_ray *objray);
void			get_hnn_infcylinder(t_vec_3d hitpos, t_vec_3d normal,
								t_ray const objray);
t_bool			intersect_ray_cylinder(t_ray *objray);
void			get_hnn_cylinder(t_vec_3d hitpos, t_vec_3d normal,
									t_ray const objray);

/*
** paraboloid.c
*/
t_bool			intersect_ray_paraboloid(t_ray *objray);
void			get_hnn_paraboloid(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray);
t_bool			intersect_ray_saddle(t_ray *objray);
void			get_hnn_saddle(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray);

/*
** cube.c
*/
t_bool			intersect_ray_cube(t_ray *objray);
void			get_hnn_cube(t_vec_3d hitpos,
								t_vec_3d normal, t_ray const objray);

#endif
