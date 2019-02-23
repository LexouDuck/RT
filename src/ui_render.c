/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_convert.h"
#include "libft_color.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "event.h"

void	ui_render_scrollbar(t_menulist *list)
{
	static SDL_Rect	dest = { 0, 0, TILE * 2, TILE * 2 };
	static SDL_Rect	tile = { 0, 0, TILE * 2, TILE };

	if (list->scrollbutton_up_clicked)
		list->scroll -= (list->scroll <= 0) ? 0 : 1;
	if (list->scrollbutton_down_clicked)
		list->scroll += (list->scroll >= list->scroll_max - list->scroll_view + TILE) ? 0 : 1;

	dest.h = TILE * 2;
	ui_render_icon((list->scrollbutton_up_clicked ? 21 : 20),
		list->scrollbutton_up.x,
		list->scrollbutton_up.y, FALSE);
	ui_render_icon((list->scrollbutton_down_clicked ? 29 : 28),
		list->scrollbutton_down.x,
		list->scrollbutton_down.y, FALSE);
	tile.x = TILE * (rt.ui.objects.scrollbar_clicked ? 14 : 12);
	tile.y = TILE * 12;
	dest.x = list->scrollbar.x;
	dest.y = list->scrollbar.y;
	t_f32 ratio;
	t_s32 height;
	ratio = (list->scrollbar.h / (t_f32)list->scroll_max);
	dest.y += (int)(list->scroll * ratio);
	if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
		debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
	dest.y += TILE;
	tile.y = TILE * 13;
	height = (list->scroll_view * ratio) / TILE - 2;
	for (int i = 0; i < height; ++i)
	{
		if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
			debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
		dest.y += TILE;
	}
	tile.y = TILE * 15;
	if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
		debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
	height = (list->scroll_view * ratio) / 2 - TILE / 2;
	dest.y = list->scrollbar.y + (int)(list->scroll * ratio) + height;
	tile.y = TILE * 14;
	if (SDL_BlitSurface(rt.ui.tileset, &tile, rt.sdl.window_surface, &dest))
		debug_output_error("Error during ui_render_scrollbar(): ", TRUE);
}

void	ui_render_icon_object(t_object* object, t_s32 y)
{
	static const t_u8	light = 0x50;
	static const t_u8	shade = 0x50;
	static t_u32		palette[PALETTE] = {
		0x000000, 0x0058F8, 0x3CBCFC, 0xFCFCFC };

	if (object->type == none)
		return ;
	palette[1] = object->color;
	palette[1] = (ft_color_argb32_get_r(palette[1]) < shade) ? (palette[1] & 0x00FFFF) : (palette[1] - (shade << 16));
	palette[1] = (ft_color_argb32_get_g(palette[1]) < shade) ? (palette[1] & 0xFF00FF) : (palette[1] - (shade << 8));
	palette[1] = (ft_color_argb32_get_b(palette[1]) < shade) ? (palette[1] & 0xFFFF00) : (palette[1] - (shade << 0));
	palette[3] = object->color;
	palette[3] = (ft_color_argb32_get_r(palette[3]) >= 0xFF - light) ? (palette[3] | 0xFF0000) : (palette[3] + (light << 16));
	palette[3] = (ft_color_argb32_get_g(palette[3]) >= 0xFF - light) ? (palette[3] | 0x00FF00) : (palette[3] + (light << 8));
	palette[3] = (ft_color_argb32_get_b(palette[3]) >= 0xFF - light) ? (palette[3] | 0x0000FF) : (palette[3] + (light << 0));
	palette[2] = object->color;
	if (!ui_set_palette(rt.ui.tileset, palette))
		return ;
	ui_render_icon((int)object->type - 1, 1, y * TILE, TRUE);
	ui_set_palette(rt.ui.tileset, rt.ui.pal);
}

void	ui_render_expandedproperties(t_object *object, t_s32 y)
{
	char		*tmp;

	if ((tmp = ft_u32_to_hex(object->color)))
	{
		ui_render_text("Color: #", 1, y + 2, FALSE);
		ui_render_text(       tmp, 9, y + 2, FALSE);
		free(tmp);
	}
	ui_render_control_numberbox( 1, y + 3, object->rgb.x);
	ui_render_control_numberbox(10, y + 3, object->rgb.y);
	ui_render_control_numberbox(19, y + 3, object->rgb.z);
	ui_render_text("Light:", 1, y + 6, FALSE);
	ui_render_control_numberbox( 1, y + 7, object->light.x);
	ui_render_control_numberbox(10, y + 7, object->light.y);
	ui_render_control_numberbox(19, y + 7, object->light.z);
	ui_render_text("Pos:", 1, y + 10, FALSE);
	ui_render_control_numberbox( 1, y + 11, object->pos.x);
	ui_render_control_numberbox(10, y + 11, object->pos.y);
	ui_render_control_numberbox(19, y + 11, object->pos.z);
	ui_render_text("Rot:", 1, y + 14, FALSE);
	ui_render_control_numberbox( 1, y + 15, object->rot.x);
	ui_render_control_numberbox(10, y + 15, object->rot.y);
	ui_render_control_numberbox(19, y + 15, object->rot.z);
	ui_render_text("Scale:", 1, y + 18, FALSE);
	ui_render_control_numberbox( 1, y + 19, object->scale.x);
	ui_render_control_numberbox(10, y + 19, object->scale.y);
	ui_render_control_numberbox(19, y + 19, object->scale.z);
}

void	ui_render_objects()
{
	t_s32		tmp;
	t_s32		add_height;
	t_bool		hover;
	SDL_Rect	rect;
	t_u32		i;

	rect = rt.ui.objects.rect;
	rect.h = 2;
	i = 0;
	while (i < rt.scene.object_amount)
	{
		tmp = rect.y;
		rect.y -= rt.ui.objects.scroll / TILE;
		add_height = (rt.ui.objects.expanded[i] ? OBJECT_PROPERTIES_H : 0);
		if (rt.scene.objects[i].type &&
			rect.y + add_height >= rt.ui.objects.rect.y - TILE &&
			rect.y < rt.ui.objects.rect.y + rt.ui.objects.rect.h)
		{
			hover = SDL_PointInRect(&rt.input.mouse_tile, &rect);
			if (hover || rt.ui.objects.selected[i])
				ui_render_fill((rt.ui.objects.selected[i] ? 2 : 1), rect, FALSE);
			ui_render_icon_object(&rt.scene.objects[i], rect.y);
			ui_render_text(rt.scene.objects[i].name, 4, rect.y + 1, TRUE);
			ui_render_icon((rt.ui.objects.expanded[i] ? 26 : 27),
				TILE * (UI_WIDTH_TILES - 4), TILE * rect.y, TRUE);
			if (rt.ui.objects.expanded[i])
				ui_render_expandedproperties(&rt.scene.objects[i], rect.y);
		}
		rect.y = tmp;
		rect.y += 2 + add_height;
		++i;
	}
	rt.ui.objects.scroll_max = TILE * rect.y;
	if (rt.ui.objects.scroll > rt.ui.objects.scroll_max)
		rt.ui.objects.scroll = rt.ui.objects.scroll_max;
	if (rt.ui.objects.scroll_max > rt.ui.objects.scroll_view)
		ui_render_scrollbar(&rt.ui.objects);
}

void	ui_render_menubar()
{
	t_bool		hover;
	SDL_Rect	rect;
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

void		ui_render_caminfo(t_camera *camera)
{
	char	*tmp;

	ui_render_text("Camera", UI_WIDTH_TILES + 2, 1, FALSE);

	tmp = ft_u32_to_str(camera->mode);		
	ui_render_text("Mode: ", UI_WIDTH_TILES + 2, 2, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 2, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->lat, 3);
	ui_render_text("LAT-> ", UI_WIDTH_TILES + 2, 4, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 4, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->lon, 3);
	ui_render_text("LON-> ", UI_WIDTH_TILES + 2, 5, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 5, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->zoom, 3);
	ui_render_text("Zoom: ", UI_WIDTH_TILES + 2, 6, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 6, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->tilt_angle, 3);
	ui_render_text("Tilt: ", UI_WIDTH_TILES + 2, 7, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 7, FALSE);
	if (tmp) free(tmp);

	tmp = cl_float3_to_str(&camera->anchor, 3);
	ui_render_text("Anchor", UI_WIDTH_TILES + 2, 9, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 9, FALSE);
	if (tmp) free(tmp);

	tmp = cl_float3_to_str(&camera->relative_pos, 3);
	ui_render_text("CamPos", UI_WIDTH_TILES + 2, 10, FALSE);
	ui_render_text(		tmp, UI_WIDTH_TILES + 8, 10, FALSE);
	if (tmp) free(tmp);
}
