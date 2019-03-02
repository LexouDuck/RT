/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"
#include "../rt.h"
#include "config.h"
#include "debug.h"
#include "event.h"

void	event_window_resize(t_s32 window_w, t_s32 window_h)
{
	t_bool maximized;

	maximized = (SDL_GetWindowFlags(rt.sdl.window) & SDL_WINDOW_MAXIMIZED);
	config_set(CONFIG_INDEX_MAXIMIZED, FT_Bool_To_String(maximized, FALSE));
	if (!maximized)
	{
		if (window_w == 0 || window_h == 0)
			SDL_GetWindowSize(rt.sdl.window, &window_w, &window_h);
		else
			SDL_SetWindowSize(rt.sdl.window, window_w, window_h);
		config_set(CONFIG_INDEX_WINDOW_W, FT_S32_To_String(window_w));
		config_set(CONFIG_INDEX_WINDOW_H, FT_S32_To_String(window_h));
		SDL_DestroyTexture(rt.sdl.window_texture);
		SDL_FreeSurface(rt.sdl.window_surface);
		init_window_display();
		rt.scene.work_dim[0] = rt.canvas_w;
		rt.scene.work_dim[1] = rt.canvas_h;
		opencl_refresh_gpu_memory_buffers();
		rt.ui.objects.rect.h = rt.sdl.window_h - rt.ui.objects.rect.y;
		rt.ui.objects.scrollbar.scroll_view = (rt.sdl.window_h - MENUBAR_ITEMS_H);
		rt.ui.objects.scrollbar.bar.h = (rt.sdl.window_h - MENUBAR_ITEMS_H) - TILE * 4;
		rt.ui.objects.scrollbar.button_down.y = rt.sdl.window_h - TILE * 2;
	}
}

void	event_window_fullscreen(t_bool fullscreen)
{
	rt.sdl.fullscreen = fullscreen;
	config_set(CONFIG_INDEX_FULLSCREEN, FT_Bool_To_String(fullscreen, FALSE));
	if (fullscreen)
	{
		if (SDL_SetWindowFullscreen(rt.sdl.window, SDL_WINDOW_FULLSCREEN_DESKTOP))
			debug_output_error(
				"Error while trying to set fullscreen mode: ", TRUE);
	}
	else
	{
		if (SDL_SetWindowFullscreen(rt.sdl.window, 0))
			debug_output_error(
				"Error while trying to restore windowed mode: ", TRUE);
	}
}

void	event_window_mouse_enter(void)
{
}

void	event_window_mouse_leave(void)
{
}
