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

# include "src/ui.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define WINDOW_TITLE	"RT: 42 Raytracer"

# define FRAMERATE	60
# define FRAME_MS	(1000 / FRAMERATE)

/*
**	This struct holds all info for the global state of the program.
*/
typedef struct		t_rt
{
	SDL_Window*		window;
	SDL_Renderer*	window_renderer;
	SDL_Texture*	window_texture;
	SDL_Surface*	window_surface;
	t_bool			must_render;
	SDL_Surface*	canvas;
	t_bool			fullscreen;
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
**                               Event handling                               *|
** ************************************************************************** *|
*/

# define KEY_ALT		0b00000011
# define KEY_ALT_L		0b00000001
# define KEY_ALT_R		0b00000010

# define KEY_CTRL		0b00001100
# define KEY_CTRL_L		0b00000100
# define KEY_CTRL_R		0b00001000

# define KEY_SHIFT		0b00110000
# define KEY_SHIFT_L	0b00010000
# define KEY_SHIFT_R	0b00100000

/*
**	event.c
**	event_window.c
*/
t_bool	event_checkevents(SDL_Window *window);
void	event_window_resize(SDL_Window *window, t_s32 window_w, t_s32 window_h);
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
**	camera.c
*/
//void	camera_update(t_sprite* target);

/*
**	render.c
*/
int		render_init();
void	render();

void		render_text(
	char* str,
	t_s32 x,
	t_s32 y,
	t_bool colored);

void	render_rect(
	t_s32 x,
	t_s32 y,
	t_u8 w,
	t_u8 h);

#endif
