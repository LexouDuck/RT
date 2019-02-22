/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "event.h"

void	event_check_keydown(SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		if (rt.sdl.fullscreen)
		{
			event_window_fullscreen(FALSE);
		}
	if (event->key.keysym.sym == SDLK_RETURN)
		if (!(rt.sdl.fullscreen) && (rt.input.keys & KEY_ALT))
		{
			event_window_fullscreen(TRUE);
		}
	// press space to refresh render
	if (event->key.keysym.sym == SDLK_SPACE)
		rt.must_render = TRUE;

	// set modifier key flags to be on
	if (event->key.keysym.sym == SDLK_LALT)
		rt.input.keys |= KEY_ALT_L;
	else if (event->key.keysym.sym == SDLK_RALT)
		rt.input.keys |= KEY_ALT_R;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		rt.input.keys |= KEY_CTRL_L;
	else if (event->key.keysym.sym == SDLK_RCTRL)
		rt.input.keys |= KEY_CTRL_R;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		rt.input.keys |= KEY_SHIFT_L;
	else if (event->key.keysym.sym == SDLK_RSHIFT)
		rt.input.keys |= KEY_SHIFT_R;
}

void	event_check_keyup(SDL_Event *event)
{
	// set modifier key flags to be off
	if (event->key.keysym.sym == SDLK_LALT)
		rt.input.keys &= ~KEY_ALT_L;
	else if (event->key.keysym.sym == SDLK_RALT)
		rt.input.keys &= ~KEY_ALT_R;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		rt.input.keys &= ~KEY_CTRL_L;
	else if (event->key.keysym.sym == SDLK_RCTRL)
		rt.input.keys &= ~KEY_CTRL_R;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		rt.input.keys &= ~KEY_SHIFT_L;
	else if (event->key.keysym.sym == SDLK_RSHIFT)
		rt.input.keys &= ~KEY_SHIFT_R;
}
