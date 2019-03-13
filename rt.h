/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_H
# define __RT_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include "SDL.h"
# include "libft.h"
# include "libft_io.h"

# include "src/config.h"
# include "src/event.h"
# include "src/ui.h"
# include "src/rt_cl.h"
# include "src/rt_scene.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define WINDOW_TITLE	"RT: 42 Raytracer"

# define FRAMERATE	60
# define FRAME_MS	(1000 / FRAMERATE)

/*
**	This struct contains information relative to the full image in window.
*/
typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*window_renderer;
	SDL_Texture		*window_texture;
	SDL_Surface		*display;
	int				window_w;
	int				window_h;
	t_bool			fullscreen;
	t_u64			current_frame;
	t_bool			loop;
}				t_sdl;

/*
**	This struct holds all info for the global state of the program.
*/
typedef struct	s_rt
{
	t_sdl			sdl;
	t_cl			ocl;
	t_config		config;
	t_input			input;
	t_scene			scene;
	SDL_Surface		*canvas;
	int				canvas_w;
	int				canvas_h;
	t_u32			canvas_pixel_amount;
	t_bool			must_render;
	char			*filepath;
	t_ui			ui;
	t_u32			random_value;
	t_u32			*img_texture;
}				t_rt;
/*
**	This is our global variable which stores everything.
*/
t_rt			g_rt;

/*
** ************************************************************************** *|
**                                 RT File I/O                                *|
** ************************************************************************** *|
*/

typedef struct	s_rtparser
{
	char		*file;
	int			index;
	int			line;
	int			current_object;
}				t_rtparser;

/*
**	init.c
*/
int				init_sdl(void);
int				init_window(void);
int				init_window_display(void);

/*
**	init_image_texture.c
*/
void			rt_get_img_texture(cl_uint **img_texture);

/*
**	rt_scene.c
*/
void			init_scene(void);
void			update_scene(void);
void			remove_selected_objects(void);
void			int_to_valid_pow_of_2(
				cl_uint *value, t_u32 max, t_u32 paired_value);
void			ui_update_control_numberbox_int(cl_uint *value);
/*
**	rt_object.c
*/
void			init_object(t_object *object);
void			update_object(t_object *object);

/*
**	ui_menu_file.c
*/
void			ui_menu_file_open(void);
void			ui_menu_file_import(void);
/*
**	ui_menu_edit.c
*/
void			ui_menu_edit_undo(void);
void			ui_menu_edit_redo(void);
void			ui_menu_edit_cut(void);
void			ui_menu_edit_copy(void);
void			ui_menu_edit_paste(void);
/*
**	ui_menu_view.c
*/
void			ui_menu_view_orthogonal(void);

/*
**	rt_get_str.c
*/
char			*rt_get_str_primitive(t_primitive primitive);
char			*rt_get_str_material(t_material material);
char			*rt_get_str_rendermode(t_rendermode rendermode);
char			*rt_get_str_cameramodel(t_camera_model cameramodel);
char			*rt_get_str_pattern(t_pattern pattern);
char			*rt_get_str_projection(t_projection projection);
char			*rt_get_str_bump(t_bump bump_type);

/*
**	rt_file.c
*/
int				rt_file_open(char *filepath);
int				rt_file_import(char *filepath);
int				rt_file_save(char *filepath);

/*
**	rt_save.c
*/
void			rt_save(int	fd);

/*
**	rt_open.c
**	rt_open_util.c
**	rt_open_read.c
*/
int				rt_open_file(char *filepath, t_rtparser *p);
char			*rt_read_object_arg(t_rtparser *p, t_object *object);
void			rt_read_getprimitive(char const *label, t_primitive *shape);
char			*rt_read_file(t_rtparser *p);
void			rt_read_whitespace(t_rtparser *p);
char			*rt_read_error(char expected, char *description, char instead);
char			*rt_read_arg_name(t_rtparser *p, char *result);
char			*rt_read_arg_number(t_rtparser *p, cl_float *result,
				char const *label);
char			*rt_read_arg_vector(t_rtparser *p, cl_float3 *result,
				char const *label);
char			*rt_read_arg_color(t_rtparser *p, cl_float3 *result,
				char const *label);
char			*rt_read_arg_material(t_rtparser *p, t_material *result,
				char const *label);
char			*rt_read_arg_pattern(t_rtparser *p, t_pattern *result,
				char const *label);
char			*rt_read_arg_projection(t_rtparser *p, t_projection *result,
				char const *label);
char			*rt_read_arg_bump(t_rtparser *p, t_bump *result,
				char const *label);

/*
**	render.c
**	update_window.c
*/
int				render(void);
void			update_window(void);

#endif
