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

# include "src/ui.h"
# include "src/rt_cl.h"
# include "src/config.h"

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
}					t_sdl;

/*
**	This struct holds all info for the global state of the program.
*/
typedef struct		t_rt
{
	t_sdl			sdl;
	t_cl			ocl;
	t_config		config;
//	t_scene			scene;	
	SDL_Surface*	canvas;
	int				canvas_w;
	int				canvas_h;
	t_u32			canvas_pixels;
	t_bool			must_render;
	t_ui			ui;
	t_u32			mouse_button;
	SDL_Point		mouse;
}					t_rt;

t_rt				rt;

/*
**	init.c
*/
int		init_sdl();
int		init_window();
int		init_window_display();

/*
** ************************************************************************** *|
**                                 RT File I/O                                *|
** ************************************************************************** *|
*/

/*
void		rt_read_whitespace(t_parser *parser);
char		*rt_read_file(t_rtv1 *rtv1, t_parser *parser, int fd);
char		*rt_read_arg_vector(t_parser *parser, t_vector *result);
char		*rt_read_arg_number(t_parser *parser, float *result);
char		*rt_read_arg_color(t_parser *parser, t_u32 *result);
*/

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
int		render_init();
void	render();

#endif