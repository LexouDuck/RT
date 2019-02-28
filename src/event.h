/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EVENT_H
# define __EVENT_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include "libft.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	These bitflags are used with rt.keys
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
**	This struct describes the current state of user inputs on the window
*/
typedef struct	s_input
{
	t_u8		keys;
	t_u32		mouse_button;
	SDL_Point	mouse;
	SDL_Point	mouse_tile;
}				t_input;

/*
**	event.c
*/
void			event_checkevents();

/*
**	event_window.c
*/
void			event_window_resize(t_s32 window_w, t_s32 window_h);
void			event_window_fullscreen(t_bool fullscreen);
void			event_window_mouse_enter();
void			event_window_mouse_leave();

/*
**	event_mouse.c
*/
void			event_check_keydown(SDL_Event *event);
void			event_check_keyup(SDL_Event *event);

/*
**	event_key.c
*/
void			event_mouse_wheel(SDL_Event *event);
void			event_mouse_press(SDL_Event *event);
void			event_mouse_release(SDL_Event *event);
void			event_mouse_motion(SDL_Event *event);

#endif
