/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
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

void	render_ui_icon_object(t_object* object, t_s32 y)
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
	render_ui_icon((int)object->type - 1, 1, y, TRUE);
	ui_set_palette(rt.ui.tileset, rt.ui.pal);
}

void	render_ui_expandedproperties(t_object *object, t_s32 y)
{
	char		*tmp;

	if ((tmp = ft_u32_to_hex(object->color)))
	{
		render_ui_text("Color: #", 1, y + 2, FALSE);
		render_ui_text(       tmp, 9, y + 2, FALSE);
		free(tmp);
	}
	if ((tmp = cl_float3_to_str(&object->rgb, 4)))
	{
		render_ui_text(tmp, 4, y + 3, FALSE);
		free(tmp);
	}
	if ((tmp = cl_float3_to_str(&object->light, 4)))
	{
		render_ui_text("Light:", 1, y + 5, FALSE);
		render_ui_text(     tmp, 4, y + 6, FALSE);
		free(tmp);
	}
	if ((tmp = cl_float3_to_str(&object->pos, 2)))
	{
		render_ui_text("Pos:", 1, y + 8, FALSE);
		render_ui_text(   tmp, 4, y + 9, FALSE);
		free(tmp);
	}
	if ((tmp = cl_float3_to_str(&object->rot, 2)))
	{
		render_ui_text("Rot:", 1, y + 11, FALSE);
		render_ui_text(   tmp, 4, y + 12, FALSE);
		free(tmp);
	}
	if ((tmp = cl_float3_to_str(&object->scale, 2)))
	{
		render_ui_text("Scale:", 1, y + 14, FALSE);
		render_ui_text(     tmp, 4, y + 15, FALSE);
		free(tmp);
	}
}

void	render_ui_objects()
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s32		i;

	rect.x = 0;
	rect.y = 4;
	rect.w = UI_WIDTH_TILES - 1;
	rect.h = 2;
	i = -1;
	while (++i < OBJECT_MAX_AMOUNT)
	{
		hover = FALSE;
		if (rt.scene.objects[i].type == none)
			continue ;
		if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
		{
			hover = TRUE;
		}
		if (hover || rt.ui.objects_selected[i])
			render_ui_fill((rt.ui.objects_selected[i] ? 2 : 1), rect, FALSE);
		render_ui_icon_object(&rt.scene.objects[i], rect.y);
		render_ui_text(rt.scene.objects[i].name, 4, rect.y + 1, TRUE);
		render_ui_text((rt.ui.objects_expanded[i] ? "\xFE" : "\xFF"),
			UI_WIDTH_TILES - 3, rect.y + 1, TRUE);
		if (rt.ui.objects_expanded[i])
			render_ui_expandedproperties(&rt.scene.objects[i], rect.y);
		rect.y += 2 + (rt.ui.objects_expanded[i] ? 3 * OBJECT_PROPERTIES : 0);
	}
}

void	render_ui_menubar()
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s8		i;

	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		hover = FALSE;
		rect = rt.ui.menubar.item_hitbox[i];
		if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
		{
			hover = TRUE;
		}
		render_ui_rect(rect, hover);
		render_ui_text(rt.ui.menubar.item_labels[i],
			rt.ui.menubar.item_hitbox[i].x + 2, 1, TRUE);
	}
}

void	render_ui_dropdown(t_menu *dropdown)
{
	t_bool		hover;
	SDL_Rect	rect;
	t_s8		i;

	i = -1;
	while (++i < dropdown->item_amount)
	{
		hover = FALSE;
		rect = dropdown->item_hitbox[i];
		if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
		{
			hover = TRUE;
		}
		render_ui_rect(rect, hover);
		render_ui_text(dropdown->item_labels[i],
			2, 3 + 2 * i, TRUE);
	}
}

void		render_ui_caminfo(t_camera *camera)
{
	char	*tmp;

	render_ui_text("Camera", UI_WIDTH_TILES + 2, 1, FALSE);

	tmp = ft_u32_to_str(camera->mode);		
	render_ui_text("Mode: ", UI_WIDTH_TILES + 2, 2, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 2, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->lat, 3);
	render_ui_text("LAT-> ", UI_WIDTH_TILES + 2, 4, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 4, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->lon, 3);
	render_ui_text("LON-> ", UI_WIDTH_TILES + 2, 5, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 5, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->zoom, 3);
	render_ui_text("Zoom: ", UI_WIDTH_TILES + 2, 6, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 6, FALSE);
	if (tmp) free(tmp);

	tmp = ft_f32_to_str(camera->tilt_angle, 3);
	render_ui_text("Tilt: ", UI_WIDTH_TILES + 2, 7, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 7, FALSE);
	if (tmp) free(tmp);

	tmp = cl_float3_to_str(&camera->anchor, 3);
	render_ui_text("Anchor", UI_WIDTH_TILES + 2, 9, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 9, FALSE);
	if (tmp) free(tmp);

	tmp = cl_float3_to_str(&camera->relative_pos, 3);
	render_ui_text("CamPos", UI_WIDTH_TILES + 2, 10, FALSE);
	render_ui_text(		tmp, UI_WIDTH_TILES + 8, 10, FALSE);
	if (tmp) free(tmp);
}
