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

#ifndef RT_H
# define RT_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include <math.h>

# include "SDL.h"
# include "libft.h"

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

/*
**	init.c
*/
int		init_sdl();
int		init_window(SDL_Window **window);
int		init_screen(SDL_Window *window,
	SDL_Texture **screen,
	SDL_Renderer **renderer);

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
**	camera.c
*/
//void	camera_update(t_sprite* target);

/*
**	render.c
*/
void	render_init();
void	render(SDL_Texture *screen, SDL_Renderer *renderer);

#endif
