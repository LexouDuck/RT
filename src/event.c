/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 13:13:18 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "event.h"

static void	event_check_window(SDL_Event *event)
{
	if (event->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		if (!g_rt.sdl.fullscreen)
			event_window_resize(0, 0);
		g_rt.must_render = TRUE;
	}
	else if (event->window.event == SDL_WINDOWEVENT_ENTER)
		event_window_mouse_enter();
	else if (event->window.event == SDL_WINDOWEVENT_LEAVE)
		event_window_mouse_leave();
}

static void	event_check_textinput(SDL_Event *event)
{
	char	*tmp;

	if (!((g_rt.input.keys & KEY_CTRL) && (
		(event->text.text[0] == 'c' || event->text.text[0] == 'C') ||
		(event->text.text[0] == 'v' || event->text.text[0] == 'V'))))
	{
		tmp = g_rt.ui.current_textinput.input;
		g_rt.ui.current_textinput.input =
			ft_strjoin(tmp ? tmp : "", event->text.text);
		if (tmp)
			free(tmp);
		g_rt.ui.current_textinput.value_changed = TRUE;
	}
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

void		event_checkevents(void)
{
	SDL_Event	event;

	g_rt.input.mouse_button =
		SDL_GetMouseState(&g_rt.input.mouse.x, &g_rt.input.mouse.y);
	g_rt.input.mouse_tile.x = (g_rt.input.mouse.x) / TILE;
	g_rt.input.mouse_tile.y = (g_rt.input.mouse.y) / TILE;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			g_rt.sdl.loop = FALSE;
			return ;
		}
		else if (event.type == SDL_WINDOWEVENT)
			event_check_window(&event);
		else if (event.type == SDL_KEYDOWN)
			event_check_keydown(&event);
		else if (event.type == SDL_KEYUP)
			event_check_keyup(&event);
		else if (event.type == SDL_TEXTINPUT)
			event_check_textinput(&event);
		else
			event_check_mouse(&event);
	}
}
