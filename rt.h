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

//# include <math.h>

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
typedef struct		s_sdl
{
	SDL_Window*		window;
	SDL_Renderer*	window_renderer;
	SDL_Texture*	window_texture;
	SDL_Surface*	window_surface;
	int				window_w;
	int				window_h;
	t_bool			fullscreen;
	t_u64			current_frame;
	t_bool			loop;
}					t_sdl;

/*
**	This struct holds all info for the global state of the program.
*/
typedef struct		t_rt
{
	t_sdl			sdl;
	t_cl			ocl;
	t_config		config;
	t_input			input;
	t_scene			scene;
	SDL_Surface*	canvas;
	int				canvas_w;
	int				canvas_h;
	t_u32			canvas_pixel_amount;
	t_bool			must_render;
	char			*filepath;
	t_ui			ui;
}					t_rt;
/*
**	This is our global variable which stores everything.
*/
t_rt				rt;

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
int			init_sdl();
int			init_window();
int			init_window_display();

/*
**	scene.c
*/
void		init_scene();
void		update_scene();
void		update_object(t_object *object);

/*
**	ui_menu_file.c
*/
void		ui_menu_file_open();
void		ui_menu_file_import();
/*
**	ui_menu_edit.c
*/
void		ui_menu_edit_undo();
void		ui_menu_edit_redo();
void		ui_menu_edit_cut();
void		ui_menu_edit_copy();
void		ui_menu_edit_paste();
/*
**	ui_menu_view.c
*/
void		ui_menu_view_orthogonal();

/*
**	rt_get_str.c
*/
char		*rt_get_str_primitive(t_primitive primitive);
char		*rt_get_str_material(t_material material);
char		*rt_get_str_rendermode(t_rendermode rendermode);
char		*rt_get_str_cameramodel(t_rendermode cameramodel);

/*
**	rt_file.c
*/
int			rt_file_open(char *filepath);
int			rt_file_import(char *filepath);
int			rt_file_save(char *filepath);

/*
**	rt_save.c
*/
void		rt_save(int	fd);
/*
**	rt_open.c
**	rt_open_util.c
**	rt_open_read.c
*/
int			rt_open_file(char *filepath, t_rtparser *p);
char		*rt_read_file(t_rtparser *p);
void		rt_output_readfile();
void		rt_read_whitespace(t_rtparser *p);
char		*rt_read_error(char expected, char *description, char instead);
char		*rt_read_arg_name(t_rtparser *p, char *result);
char		*rt_read_arg_number(t_rtparser *p, float *result);
char		*rt_read_arg_vector(t_rtparser *p, cl_float3 *result, char const* label);
char		*rt_read_arg_color(t_rtparser *p, cl_float3 *result, char const* label);
char		*rt_read_arg_material(t_rtparser *p, t_material *result, char const *label);

/*
** ************************************************************************** *|
**                                 Rendering                                  *|
** ************************************************************************** *|
*/

/*
**	camera.c
*/
//void	camera_update(t_sprite* target);

/*
**	render.c
*/
int		render();

#endif
