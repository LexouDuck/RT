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

void	ui_render_menubar(void)
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s32		y;
	t_s32		i;

	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = rt.ui.menubar.item_hitbox[i];
		hover = SDL_PointInRect(&rt.input.mouse_tile, &rect);
		ui_render_rect(rect, hover);
		ui_render_text(rt.ui.menubar.item_labels[i],
			rt.ui.menubar.item_hitbox[i].x + 2, 1, TRUE);
	}
	rect.x = 0;
	rect.y = MENUBAR_ITEMS_H;
	rect.w = UI_WIDTH_TILES;
	rect.h = 7;
	ui_render_fill(0, rect, FALSE);
	y = rect.y;
	ui_render_text("Render Mode:", 2, y, FALSE);
	ui_render_text("\x12", 14, y, TRUE);
	ui_render_text("\x13", 27, y, TRUE);
	ui_render_text(rt_get_str_rendermode(rt.scene.render_mode), 15, y, FALSE);
	y += 2;
	ui_render_text("Camera Type:", 2, y, FALSE);
	ui_render_text("\x12", 14, y, TRUE);
	ui_render_text("\x13", 27, y, TRUE);
	ui_render_text(rt_get_str_cameramodel(rt.scene.camera.model), 15, y, FALSE);
	y += 1;
	ui_render_text("FOV:", 1, y, FALSE);
	ui_render_text("Aperture:", 7, y, FALSE);
	ui_render_text("FocalDist:", 18, y, FALSE);
	y += 1;
	ui_render_control_numberbox( 1, y, &rt.scene.camera.hrz_fov);
	ui_render_control_numberbox(10, y, &rt.scene.camera.aperture);
	ui_render_control_numberbox(19, y, &rt.scene.camera.focal_dist);


}

void	ui_render_dropdown(t_menu *dropdown)
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s32		i;

	i = -1;
	while (++i < dropdown->item_amount)
	{
		rect = dropdown->item_hitbox[i];
		hover = SDL_PointInRect(&rt.input.mouse_tile, &rect);
		ui_render_rect(rect, hover);
		ui_render_text(dropdown->item_labels[i],
			2, 3 + 2 * i, TRUE);
	}
}

void	ui_render_prompt(void)
{
	SDL_Rect button;

	ui_render_rect(rt.ui.current_prompt.rect, FALSE);
	ui_render_text(rt.ui.current_prompt.name,
		rt.ui.current_prompt.rect.x + 2, rt.ui.current_prompt.rect.y + 0, TRUE);
	ui_render_text(rt.ui.current_prompt.description,
		rt.ui.current_prompt.rect.x + 2, rt.ui.current_prompt.rect.y + 2, FALSE);
	ui_render_control_textbox(2, 8, rt.ui.current_textinput.value);
	button = PROMPT_BUTTON_OK;
	ui_render_rect(button, SDL_PointInRect(&rt.input.mouse_tile, &button));
	ui_render_text("OK", button.x + 3, button.y + 1, TRUE);
	button = PROMPT_BUTTON_CANCEL;
	ui_render_rect(button, SDL_PointInRect(&rt.input.mouse_tile, &button));
	ui_render_text("CANCEL", button.x + 1, button.y + 1, TRUE);
}

void	ui_render_caminfo(t_camera *camera)
{
	char	*tmp;

	ui_render_text("Camera", UI_WIDTH_TILES + 2, 1, FALSE);
	tmp = ft_u32_to_str(camera->mode);
	ui_render_text("Mode: ", UI_WIDTH_TILES + 2, 2, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 2, FALSE);
	if (tmp)
		free(tmp);
	tmp = ft_f32_to_str(camera->lat, 3);
	ui_render_text("LAT-> ", UI_WIDTH_TILES + 2, 4, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 4, FALSE);
	if (tmp)
		free(tmp);
	tmp = ft_f32_to_str(camera->lon, 3);
	ui_render_text("LON-> ", UI_WIDTH_TILES + 2, 5, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 5, FALSE);
	if (tmp)
		free(tmp);
	tmp = ft_f32_to_str(camera->zoom, 3);
	ui_render_text("Zoom: ", UI_WIDTH_TILES + 2, 6, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 6, FALSE);
	if (tmp)
		free(tmp);
	tmp = ft_f32_to_str(camera->tilt_angle, 3);
	ui_render_text("Tilt: ", UI_WIDTH_TILES + 2, 7, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 7, FALSE);
	if (tmp)
		free(tmp);
	tmp = cl_float3_to_str(&camera->anchor, 3);
	ui_render_text("Anchor", UI_WIDTH_TILES + 2, 9, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 9, FALSE);
	if (tmp)
		free(tmp);
	tmp = cl_float3_to_str(&camera->relative_pos, 3);
	ui_render_text("CamPos", UI_WIDTH_TILES + 2, 10, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 10, FALSE);
	if (tmp)
		free(tmp);
}

void	ui_render_loading_bar(void)
{
	float	percent;
	char	*tmp;

	percent = rt.ocl.render_progress * 100.;
	tmp = ft_f32_to_str(percent, 3);
	tmp[ft_strlen(tmp) - 2] = ' ';
	tmp[ft_strlen(tmp) - 1] = '%';
	ui_render_text("Render", UI_WIDTH_TILES + 2, 11, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 11, FALSE);
	if (tmp)
		free(tmp);
}
