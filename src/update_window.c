/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets.h"
#include "../rt.h"
#include "debug.h"
#include "ui.h"
#include "rt_scene.h"

/*
** Fill the window pixel buffer with black
** Display the UI
** Do the 3d render if needed
*/

static void		update_window_display(void)
{
	SDL_Rect	dest;

	if (SDL_FillRect(g_rt.sdl.display, NULL, 0x000000))
		debug_output_error(
			"Error during update_window() -> Screen clear: ", TRUE);
	if (g_rt.ui.current_prompt.name)
		ui_render_prompt();
	else
	{
		ui_render_objectlist();
		ui_render_menubar();
	}
	if (g_rt.ui.menubar.selection != -1)
		ui_render_dropdown(&g_rt.ui.dropdowns[g_rt.ui.menubar.selection]);
	if (g_rt.must_render)
		render();
	dest = g_rt.sdl.display->clip_rect;
	dest.x += UI_WIDTH;
	dest.w -= UI_WIDTH;
	if (SDL_BlitSurface(
		g_rt.canvas, &g_rt.canvas->clip_rect, g_rt.sdl.display, &dest))
		debug_output_error(
			"Error during update_window() -> render blit: ", TRUE);
	ui_render_caminfo(&g_rt.scene.camera);
	ui_render_loading_bar();
}

void			update_window(void)
{
	update_window_display();
	if (SDL_UpdateTexture(
		g_rt.sdl.window_texture, NULL,
		g_rt.sdl.display->pixels, g_rt.sdl.display->pitch))
		debug_output_error("Error during window update: ", TRUE);
	if (SDL_RenderCopy(
		g_rt.sdl.window_renderer, g_rt.sdl.window_texture, NULL, NULL))
		debug_output_error("Error during render copy: ", TRUE);
	SDL_RenderPresent(g_rt.sdl.window_renderer);
	g_rt.must_render = FALSE;
}
