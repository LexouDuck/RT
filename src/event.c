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

static void	event_check_window(SDL_Event *event, SDL_Window *window)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (!rt.sdl.fullscreen)
			event_window_resize(window, 0, 0);
	}
}

static void	event_check_keydown(SDL_Event *event, SDL_Window *window,
	t_u8 *keys)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		if (rt.sdl.fullscreen)
		{
			rt.sdl.fullscreen = FALSE;
			event_window_fullscreen(window, FALSE);
		}
	if (event->key.keysym.sym == SDLK_RETURN)
		if (!(rt.sdl.fullscreen) && (*keys & KEY_ALT))
		{
			rt.sdl.fullscreen = TRUE;
			event_window_fullscreen(window, TRUE);
		}
	if (event->key.keysym.sym == SDLK_SPACE)
		rt.must_render = TRUE;

	// set modifier key flags to be on
	if (event->key.keysym.sym == SDLK_LALT)
		*keys |= KEY_ALT_L;
	else if (event->key.keysym.sym == SDLK_RALT)
		*keys |= KEY_ALT_R;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		*keys |= KEY_CTRL_L;
	else if (event->key.keysym.sym == SDLK_RCTRL)
		*keys |= KEY_CTRL_R;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		*keys |= KEY_SHIFT_L;
	else if (event->key.keysym.sym == SDLK_RSHIFT)
		*keys |= KEY_SHIFT_R;
}

static void	event_check_keyup(SDL_Event *event,
	t_u8 *keys)
{
	// set modifier key flags to be off
	if (event->key.keysym.sym == SDLK_LALT)
		*keys &= ~KEY_ALT_L;
	else if (event->key.keysym.sym == SDLK_RALT)
		*keys &= ~KEY_ALT_R;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		*keys &= ~KEY_CTRL_L;
	else if (event->key.keysym.sym == SDLK_RCTRL)
		*keys &= ~KEY_CTRL_R;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		*keys &= ~KEY_SHIFT_L;
	else if (event->key.keysym.sym == SDLK_RSHIFT)
		*keys &= ~KEY_SHIFT_R;
}

/*
static void	event_check_mouse(SDL_Event *event)
{

}
*/

t_bool		event_checkevents(SDL_Window *window)
{
	static t_u8	keys = 0;
	SDL_Event	event;

	rt.sdl.fullscreen = (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP);
	while (SDL_PollEvent(&event))
	{	// Handle events on queue
		if (event.type == SDL_QUIT)
		    return (FALSE);
		else if (event.type == SDL_WINDOWEVENT)
			event_check_window(&event, window);
		else if (event.type == SDL_KEYDOWN)
			event_check_keydown(&event, window, &keys);
		else if (event.type == SDL_KEYUP)
			event_check_keyup(&event, &keys);
//		else if (event.type == SDL_MOUSEBUTTONDOWN)
//			event_check_mouse(&event);
	}
	return (TRUE);
}
