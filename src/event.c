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

static void	event_check_window(SDL_Event *event, SDL_Window *window)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (!rt.sdl.fullscreen)
			event_window_resize(window, 0, 0);
		rt.must_render = TRUE;
	}
}

static void	event_check_keydown(SDL_Event *event, SDL_Window *window)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		if (rt.sdl.fullscreen)
		{
			rt.sdl.fullscreen = FALSE;
			event_window_fullscreen(window, FALSE);
		}
	if (event->key.keysym.sym == SDLK_RETURN)
		if (!(rt.sdl.fullscreen) && (rt.input.keys & KEY_ALT))
		{
			rt.sdl.fullscreen = TRUE;
			event_window_fullscreen(window, TRUE);
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

static void	event_check_keyup(SDL_Event *event)
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

/*
static void	event_check_mouse(SDL_Event *event)
{

}
*/

t_bool		event_checkevents(SDL_Window *window)
{
	SDL_Event	event;

	rt.input.mouse_button =
		SDL_GetMouseState(&rt.input.mouse.x, &rt.input.mouse.y);
	rt.sdl.fullscreen =
		(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP);
	while (SDL_PollEvent(&event))
	{	// Handle events on queue
		if (event.type == SDL_QUIT)
		    return (FALSE);
		else if (event.type == SDL_WINDOWEVENT)
			event_check_window(&event, window);
		else if (event.type == SDL_KEYDOWN)
			event_check_keydown(&event, window);
		else if (event.type == SDL_KEYUP)
			event_check_keyup(&event);
//		else if (event.type == SDL_MOUSEBUTTONDOWN)
//			event_check_mouse(&event);
	}
	return (TRUE);
}
