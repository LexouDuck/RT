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

static void	event_check_window(SDL_Event *event)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (!rt.sdl.fullscreen)
			event_window_resize(0, 0);
		rt.must_render = TRUE;
	}
	else if (event->window.event == SDL_WINDOWEVENT_ENTER)
		event_window_mouse_enter();
	else if (event->window.event == SDL_WINDOWEVENT_LEAVE)
		event_window_mouse_leave();
}

static void	event_check_mouse(SDL_Event *event)
{
	if (!event)
		return ;
	else if (event->type == SDL_MOUSEWHEEL)
		event_mouse_wheel(event);
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		event_mouse_press(event);
	else if (event->type == SDL_MOUSEBUTTONUP)
		event_mouse_release(event);
	else if (event->type == SDL_MOUSEMOTION)
		event_mouse_motion(event);
}

t_bool		event_checkevents()
{
	SDL_Event	event;

	rt.input.mouse_button =
		SDL_GetMouseState(&rt.input.mouse.x, &rt.input.mouse.y);
	rt.input.mouse_tile.x = (rt.input.mouse.x) / TILE;
	rt.input.mouse_tile.y = (rt.input.mouse.y) / TILE;
	while (SDL_PollEvent(&event))
	{	// Handle events on queue
		if (event.type == SDL_QUIT)
		    return (FALSE);
		else if (event.type == SDL_WINDOWEVENT)
			event_check_window(&event);
		else if (event.type == SDL_KEYDOWN)
			event_check_keydown(&event);
		else if (event.type == SDL_KEYUP)
			event_check_keyup(&event);
		else
			event_check_mouse(&event);
	}
	return (TRUE);
}
