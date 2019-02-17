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
	t_ui			ui;
}					t_rt;

t_rt				rt;

/*
**	init.c
*/
int		init_sdl();
int		init_window();
int		init_window_display();
void	init_scene();

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

int			rt_open_file(char *filepath);
void		rt_read_whitespace(t_rtparser *p);
char		*rt_read_error(char expected, char *description, char instead);
char		*rt_read_arg_vector(t_rtparser *p, cl_float3 *result);
char		*rt_read_arg_number(t_rtparser *p, float *result);
char		*rt_read_arg_color(t_rtparser *p, t_u32 *result);

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
