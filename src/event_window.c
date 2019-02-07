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

#include "../rt.h"
#include "config.h"
#include "debug.h"

#include "libft_convert.h"

inline void	event_window_resize(SDL_Window *window, t_s32 window_w, t_s32 window_h)
{
	t_bool maximized;

	maximized = (SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED);
	config_set(CONFIG_INDEX_MAXIMIZED, FT_Bool_To_String(maximized, FALSE));
	if (!maximized)
	{
		if (window_w == 0 || window_h == 0)
			SDL_GetWindowSize(window, &window_w, &window_h);
		else
			SDL_SetWindowSize(window, window_w, window_h);
		config_set(CONFIG_INDEX_WINDOW_W, FT_S32_To_String(window_w));
		config_set(CONFIG_INDEX_WINDOW_H, FT_S32_To_String(window_h));
		SDL_DestroyTexture(rt.sdl.window_texture);
		SDL_FreeSurface(rt.sdl.window_surface);
		init_window_display();
	}
}

inline void	event_window_fullscreen(SDL_Window *window, t_bool fullscreen)
{
	config_set(CONFIG_INDEX_FULLSCREEN, FT_Bool_To_String(fullscreen, FALSE));
	if (fullscreen)
	{
		if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP))
			debug_output_error(
				"Error while trying to set fullscreen mode: ", TRUE);
	}
	else
	{
		if (SDL_SetWindowFullscreen(window, 0))
			debug_output_error(
				"Error while trying to restore windowed mode: ", TRUE);
	}
}
