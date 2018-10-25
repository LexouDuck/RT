/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:34:32 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 16:27:20 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

/*
** NB : convention used is +x for right axis, +y for up axis, +z for back axis
*/

# include "libft/hdr/libft.h"
# include "libft/hdr/libft_algebra.h"
# include "libft/hdr/ft_printf.h"
# include "libft/hdr/get_next_line.h"
# include "mlx_event_mac.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>

# define REN_W		480
# define REN_H		360

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF
# define DBG_COLOR		0x5500BB
# define BG_COLOR		0x00BB88
# define NO_INTER		0xFF000000

# define APPROX			0.000001
# define INIT_FOV		0.8

# define MAX_LGT_NB		16
# define MAX_OBJ_NB		32
# define MAX_FILE_LN_NB	1000

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef t_u32	t_color;

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
}				t_camera;

/*
** RAYS AND SHADING
**
** Rays can be interpreted in any space.
** pos + scale(t, dir) = end of the current ray; t is init at +inf.
*/
typedef struct	s_ray
{
	t_vec_3d	pos;
	t_vec_3d	dir;
	t_float		t;
}				t_ray;

/*
** Respective intensity for light source's rgb is vec3_scale(intensity, rgb),
**	where rgb contains values between 0. and 1.
*/
typedef struct	s_light
{
	t_vec_3d	pos;
	t_float		intensity;
	t_vec_3d	rgb;
}				t_light;

typedef struct	s_shader
{
	t_ray		dirlight;
	t_vec_3d	normal;
	t_vec_3d	obj_albedo;
	t_vec_3d	obj_specul;
	t_vec_3d	objray_dir;
}				t_shader;

/*
** PRIMITIVES
**
** All primitives are considered to be centered near the origin with default
** unit dimensions.
*/
typedef enum	e_objtype
{
	null_obj,
	light,
	sphere,
	plane,
	disk,
	square,
	triangle,
	infcylinder,
	cylinder,
	infcone,
	cone,
	cube,
	paraboloid,
	saddle
}				t_objtype;

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
** albedo		: a vector of float from 0. to 1. representing how much each
**					object reflects each primary color of light,
**					respectively (r, g, b);
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

typedef t_bool	(*t_inter_func)(t_ray *objray);
typedef void	(*t_hnn_func)(t_vec_3d hp, t_vec_3d nml, t_ray const objr);

typedef struct	s_object
{
	t_objtype		type;
	t_vec_3d		pos;
	t_vec_3d		scl;
	t_vec_3d		rot;
	t_vec_3d		albedo;
	t_vec_3d		specul;
	t_mat_4b4		o_to_w;
	t_mat_4b4		w_to_o;
	t_mat_3b3		linear_o_to_w;
	t_mat_3b3		linear_w_to_o;
	t_mat_3b3		n_to_w;
	t_inter_func	intersect;
	t_hnn_func		get_hnn;
}				t_object;

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
	int				img_pixel_nb;
	int				endian;
	char			*img_data;
	t_camera		cam;
	t_float			render_dist;
	t_bool			debug;
	t_bool			show_diffuse;
	t_bool			show_specular;
	t_point			mouse;
	t_object		objlst[MAX_OBJ_NB];
	int				objlst_len;
	t_light			spotlst[MAX_LGT_NB];
	int				spotlst_len;
}				t_control;

void			exit_error(char *e_msg, int e_no);

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
*/

void			mat44_app_vec3(t_vec_3d result,
								t_mat_4b4 const mat,
								t_vec_3d const v);
t_bool			trace_ray_to_objs(t_control *ctrl, t_ray ray,
									t_object *hit_obj, t_ray *res_objray);
void			cast_rays(t_control *ctrl);

/*
** objects.c
*/
void			build_obj(t_object *obj, t_objtype type);

/*
** shader.c
*/
t_color			get_color_from_fixed_objray(t_control *ctrl,
							t_object const obj, t_ray const objray);

/*
** primitive_utils.c
*/
t_bool			get_realroots_quadpoly(t_float *root1, t_float *root2,
									t_vec_3d const quadpoly);
void			get_ray_hitpos(t_vec_3d hitpos, t_ray const objray);
void			get_reflect(t_vec_3d res,
							t_vec_3d const incident, t_vec_3d const normal);
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
