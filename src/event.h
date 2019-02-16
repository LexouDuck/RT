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
}				t_input;

/*
**	event.c
**	event_window.c
*/
t_bool	event_checkevents(SDL_Window *window);
void	event_window_resize(SDL_Window *window, t_s32 window_w, t_s32 window_h);
void	event_window_fullscreen(SDL_Window *window, t_bool fullscreen);

#endif