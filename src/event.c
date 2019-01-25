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

static void	event_check_window(SDL_Event *event,
	SDL_Window *window,
	t_bool *fullscreen)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (!*fullscreen)
			event_window_resize(window, 0, 0);
	}
}

static void	event_check_keydown(SDL_Event *event,
	SDL_Window *window,
	t_u8 *keys,
	t_bool *fullscreen)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_ESCAPE:
			if (*fullscreen)
			{
				*fullscreen = FALSE;
				event_window_fullscreen(window, FALSE);
			}
			break;

		case SDLK_RETURN:
			if (!*fullscreen && ((*keys & KEY_ALT_L) || (*keys & KEY_ALT_R)))
			{
				*fullscreen = TRUE;
				event_window_fullscreen(window, TRUE);
			}
			break;

		// resize the window to multiples of the native NES resolution when pressing number keys
		case SDLK_1: if (!*fullscreen) event_window_resize(window, WINDOW_W * 1, WINDOW_H * 1); break;
		case SDLK_2: if (!*fullscreen) event_window_resize(window, WINDOW_W * 2, WINDOW_H * 2); break;
		case SDLK_3: if (!*fullscreen) event_window_resize(window, WINDOW_W * 3, WINDOW_H * 3); break;
		case SDLK_4: if (!*fullscreen) event_window_resize(window, WINDOW_W * 4, WINDOW_H * 4); break;
		case SDLK_5: if (!*fullscreen) event_window_resize(window, WINDOW_W * 5, WINDOW_H * 5); break;

		// set modifier key flags to be on
		case SDLK_LALT:		*keys |= KEY_ALT_L;		break;
		case SDLK_RALT:		*keys |= KEY_ALT_R;		break;
		case SDLK_LCTRL:	*keys |= KEY_CTRL_L;	break;
		case SDLK_RCTRL:	*keys |= KEY_CTRL_R;	break;
		case SDLK_LSHIFT:	*keys |= KEY_SHIFT_L;	break;
		case SDLK_RSHIFT:	*keys |= KEY_SHIFT_R;	break;
	}
}

static void	event_check_keyup(SDL_Event *event, t_u8 *keys)
{
	switch (event->key.keysym.sym)
	{
		// set modifier key flags to be off
		case SDLK_LALT:		*keys &= ~KEY_ALT_L;	break;
		case SDLK_RALT:		*keys &= ~KEY_ALT_R;	break;
		case SDLK_LCTRL:	*keys &= ~KEY_CTRL_L;	break;
		case SDLK_RCTRL:	*keys &= ~KEY_CTRL_R;	break;
		case SDLK_LSHIFT:	*keys &= ~KEY_SHIFT_L;	break;
		case SDLK_RSHIFT:	*keys &= ~KEY_SHIFT_R;	break;
	}
}

t_bool		event_checkevents(SDL_Window *window)
{
	static t_u8	keys = 0;
	t_bool		fullscreen;
	SDL_Event	event;

	fullscreen = (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP);
	while (SDL_PollEvent(&event))
	{	// Handle events on queue
		if (event.type == SDL_QUIT)
		    return (FALSE);
		else if (event.type == SDL_WINDOWEVENT)
			event_check_window(&event, window, &fullscreen);
		else if (event.type == SDL_KEYDOWN)
			event_check_keydown(&event, window, &keys, &fullscreen);
		else if (event.type == SDL_KEYUP)
			event_check_keyup(&event, &keys);
	}
	return (TRUE);
}
