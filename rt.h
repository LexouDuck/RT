/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/03 19:11:13 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "SDL.h"
# include "libft.h"
# include "libft_io.h"

# ifdef __APPLE__
#  define CL_SILENCE_DEPRECATION
#  include <OpenCL/cl.h>
# else
#  include <CL/cl.h>
# endif

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define WINDOW_W	640
# define WINDOW_H	480
# define WINDOW_TITLE	"RT: 42 Raytracer"

# define FRAMERATE	60
# define FRAME_MS	(1000 / FRAMERATE)


typedef struct	s_rt_sdl
{
	SDL_Window		*window;
	SDL_Texture		*texture;
	SDL_Surface		*screen;
	SDL_Renderer	*renderer;
}				t_rt_sdl;

/*
**	init_sdl.c
** static :
** 
** int		init_window(SDL_Window **window);
** int		init_screen(SDL_Window *window,
**				SDL_Texture **screen,
**				SDL_Renderer **renderer);
*/
int		init_sdl(t_rt_sdl *sdl);

/*
** ************************************************************************** *|
**                               Event handling                               *|
** ************************************************************************** *|
*/

# define KEY_ALT_L		0b00000001
# define KEY_ALT_R		0b00000010
# define KEY_CTRL_L		0b00000100
# define KEY_CTRL_R		0b00001000
# define KEY_SHIFT_L	0b00010000
# define KEY_SHIFT_R	0b00100000

/*
**	event.c
**	event_window.c
*/
t_bool	event_checkevents(SDL_Window *window);
void	event_window_resize(SDL_Window *window, int window_w, int window_h);
void	event_window_fullscreen(SDL_Window *window, t_bool fullscreen);

/*
** ************************************************************************** *|
**                                 Rendering                                  *|
** ************************************************************************** *|
*/

typedef enum	e_cameramode
{
	CAMERA_NONE,
	CAMERA_ROTATE,
	CAMERA_TILT,
	CAMERA_PAN,
}				t_cameramode;

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
	cl_float3		world_pos;
//	cl_float3		reltv_pos;
//	cl_float3		polar_pos;
	cl_float3		anchor;
//	cl_float3		axis_x;
//	cl_float3		axis_y;
//	cl_float3		axis_z;
	cl_float		tilt;
	cl_float		hrz_fov;
//	t_mat_4b4		c_to_w;
//	t_mat_4b4		w_to_c;
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
	cl_uint		depth;
	cl_float3	lum_contrib_at_pos;
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
**
**									OpenCL
**
*/
/*
** see clBuildProgram in OpenCL API for details
// TODO experiment with optimization options
*/
# define RT_CL_PROGRAM_SOURCE		"rt_cl_render.cl"
# define RT_CL_PROGRAM_OPTIONS		"-Werror -g" //-cl-nv-verbose" //-cl-kernel-arg-info" //-cl-fast-relaxed-math" //-cl-unsafe-math-optimizations //-cl-mad-enable
# define RT_CL_KERNEL_NB			1
# define RT_CL_KERNEL_0				"rt_cl_render"

typedef struct	s_gpu
{
	//gpu info
	cl_device_id	id;
	cl_ulong		global_mem_size;
	cl_uint			comp_unit_nb;
	size_t			max_kernel_args_size;
	size_t			max_witems_per_wgroup;
	cl_uint			max_nd_range;
	size_t			max_witems_per_dim[16];//should be replaced by value of max_nd_range
	//gpu mem
	t_u8			*in_buf_hostptr;
	t_u8			*out_buf_hostptr;
	cl_mem			in_buf;
	cl_mem			out_buf;
}				t_gpu;

typedef struct	s_rt_cl
{
	cl_platform_id		platform;
	t_gpu				gpu;
	cl_context			context;
	cl_program			program;
	cl_command_queue	cmd_queue;
	cl_kernel			kernels[RT_CL_KERNEL_NB];
	cl_mem				scene_gpu_buf;
	cl_mem				result_gpu_buf;
	cl_int				status;
}				t_rt_cl;

typedef struct	s_env
{
	t_rt_sdl		sdl;
	t_rt_cl			ocl;
//	t_rt_scene		scene;
}				t_env;

/*
**	camera.c
*/
//void	camera_update(t_sprite* target);

/*
**	render.c
*/
//void	render_init(t_rt_cl *ocl);
void	render(t_rt_sdl *sdl, t_rt_cl *ocl);

/*
** init_opencl.c
*/
int		init_opencl(t_rt_cl *ocl);

#endif