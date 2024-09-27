/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 12:39:42 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "event.h"

static void	ui_render_menu_camera(t_s32 y)
{
	ui_render_text("Camera Type:", 2, y, FALSE);
	ui_render_text("\x12", 14, y, TRUE);
	ui_render_text("\x13", 27, y, TRUE);
	ui_render_text(rt_get_str_cameramodel(g_rt.scene.camera.model),
		15, y, FALSE);
	y += 1;
	ui_render_text("FOV   Aperture   FocalDist", 1, y, FALSE);
	y += 1;
	ui_render_control_numberbox_float(1, y, &g_rt.scene.camera.hrz_fov);
	ui_render_control_numberbox_float(10, y, &g_rt.scene.camera.aperture);
	ui_render_control_numberbox_float(19, y, &g_rt.scene.camera.focal_dist);
	y += 3;
	ui_render_text("Camera Light ColorMask:", 2, y, FALSE);
	y += 1;
	ui_render_control_numberbox_float(1, y, &g_rt.scene.camera.rgb_mask.x);
	ui_render_control_numberbox_float(10, y, &g_rt.scene.camera.rgb_mask.y);
	ui_render_control_numberbox_float(19, y, &g_rt.scene.camera.rgb_mask.z);
	y += 3;
	ui_render_text("Camera Shade Filter:", 2, y, FALSE);
	y += 1;
	ui_render_control_numberbox_float(1, y, &g_rt.scene.camera.rgb_shade.x);
	ui_render_control_numberbox_float(10, y, &g_rt.scene.camera.rgb_shade.y);
	ui_render_control_numberbox_float(19, y, &g_rt.scene.camera.rgb_shade.z);
}

static void	ui_render_menu(void)
{
	t_s32		y;

	y = MENUBAR_ITEMS_H;
	ui_render_text("Platform   Rays    Depth", 1, y, FALSE);
	y += 1;
	ui_render_control_numberbox_int(1, y, &g_rt.ocl.gpu_platform_index);
	ui_render_control_numberbox_int(10, y, &g_rt.scene.mc_raysamp_size);
	ui_render_control_numberbox_int(19, y, &g_rt.scene.max_ray_depth);
	y += 3;
	ui_render_text("Render Mode:", 2, y, FALSE);
	ui_render_text("\x12", 14, y, TRUE);
	ui_render_text("\x13", 27, y, TRUE);
	ui_render_text(rt_get_str_rendermode(g_rt.scene.render_mode), 15, y, FALSE);
	y += 2;
	ui_render_menu_camera(y);
}

void		ui_render_menubar(void)
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s32		i;

	rect.x = 0;
	rect.y = 0;
	rect.w = UI_WIDTH_TILES;
	rect.h = g_rt.ui.objects.rect.y;
	ui_render_fill(0, rect, FALSE);
	ui_render_icon(27,
		TILE * (UI_WIDTH_TILES - 8),
		TILE * 1, FALSE);
	ui_render_icon(26,
		TILE * (UI_WIDTH_TILES - 4),
		TILE * 1, FALSE);
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = g_rt.ui.menubar.item_hitbox[i];
		hover = SDL_PointInRect(&g_rt.input.mouse_tile, &rect);
		ui_render_rect(rect, hover);
		ui_render_text(g_rt.ui.menubar.item_labels[i],
			g_rt.ui.menubar.item_hitbox[i].x + 2, 1, TRUE);
	}
	ui_render_menu();
}

void		ui_render_dropdown(t_menu *dropdown)
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s32		i;

	i = -1;
	while (++i < dropdown->item_amount)
	{
		rect = dropdown->item_hitbox[i];
		hover = SDL_PointInRect(&g_rt.input.mouse_tile, &rect);
		ui_render_rect(rect, hover);
		ui_render_text(dropdown->item_labels[i],
			2, 3 + 2 * i, TRUE);
	}
}

void		ui_render_prompt(void)
{
	SDL_Rect prompt;
	SDL_Rect button;

	prompt = g_rt.ui.current_prompt.rect;
	ui_render_rect(prompt, FALSE);
	ui_render_text(g_rt.ui.current_prompt.name,
		prompt.x + 2, prompt.y + 0, TRUE);
	ui_render_text(g_rt.ui.current_prompt.description,
		prompt.x + 2, prompt.y + 2, FALSE);
	ui_render_control_textbox(2, 8, g_rt.ui.current_textinput.value);
	button = PROMPT_BUTTON_OK;
	ui_render_rect(button, SDL_PointInRect(&g_rt.input.mouse_tile, &button));
	ui_render_text("OK", button.x + 3, button.y + 1, TRUE);
	button = PROMPT_BUTTON_CANCEL;
	ui_render_rect(button, SDL_PointInRect(&g_rt.input.mouse_tile, &button));
	ui_render_text("CANCEL", button.x + 1, button.y + 1, TRUE);
}
