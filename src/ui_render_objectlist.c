/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render_objectlist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 12:39:42 by hbruvry          ###   ########.fr       */
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

void		ui_render_icon_object(t_object *object, t_s32 y)
{
	static const t_u8	light = 0x50;
	static const t_u8	shade = 0x50;
	static t_u32		palette[PALETTE] = {
		0x000000, 0x0058F8, 0x3CBCFC, 0xFCFCFC };

	palette[1] = object->color_a;
	palette[1] = (ft_color_argb32_get_r(palette[1]) < shade) ?
		(palette[1] & 0x00FFFF) : (palette[1] - (shade << 16));
	palette[1] = (ft_color_argb32_get_g(palette[1]) < shade) ?
		(palette[1] & 0xFF00FF) : (palette[1] - (shade << 8));
	palette[1] = (ft_color_argb32_get_b(palette[1]) < shade) ?
		(palette[1] & 0xFFFF00) : (palette[1] - (shade << 0));
	palette[3] = object->color_a;
	palette[3] = (ft_color_argb32_get_r(palette[3]) >= 0xFF - light) ?
		(palette[3] | 0xFF0000) : (palette[3] + (light << 16));
	palette[3] = (ft_color_argb32_get_g(palette[3]) >= 0xFF - light) ?
		(palette[3] | 0x00FF00) : (palette[3] + (light << 8));
	palette[3] = (ft_color_argb32_get_b(palette[3]) >= 0xFF - light) ?
		(palette[3] | 0x0000FF) : (palette[3] + (light << 0));
	palette[2] = object->color_a;
	if (object->type == none || !ui_set_palette(rt.ui.tileset, palette))
		return ;
	ui_render_icon((int)object->type - 1, 1, y * TILE, TRUE);
	ui_set_palette(rt.ui.tileset, rt.ui.pal);
}

static void	ui_render_expandedproperty(t_bool is_string,
	char const *label, void *value, t_s32 y)
{
	char const	*str;
	cl_float3	*vector;

	if (is_string)
	{
		str = (char const *)value;
		ui_render_text(label, 1, y, FALSE);
		ui_render_text(str, 13, y, FALSE);
		ui_render_text("\x12", 12, y, FALSE);
		ui_render_text("\x13", 24, y, FALSE);
	}
	else
	{
		vector = (cl_float3 *)value;
		ui_render_text(label, 1, y, FALSE);
		ui_render_control_numberbox_float(1, y + 1, &vector->x);
		ui_render_control_numberbox_float(10, y + 1, &vector->y);
		ui_render_control_numberbox_float(19, y + 1, &vector->z);
	}
}

void		ui_render_expandedproperties(t_object *object, t_s32 y)
{
	ui_render_expandedproperty(TRUE, "Primitive:",
		rt_get_str_primitive(object->type), y + 2);
	ui_render_expandedproperty(TRUE, "Material:",
		rt_get_str_material(object->material), y + 4);
	ui_render_expandedproperty(TRUE, "Pattern:",
		rt_get_str_pattern(object->pattern), y + 6);
	ui_render_expandedproperty(TRUE, "Projection:",
		rt_get_str_projection(object->uvw_projection), y + 8);
	ui_render_expandedproperty(TRUE, "Bump:",
		rt_get_str_bump(object->bump_type), y + 10);
	ui_render_expandedproperty(FALSE, "Color A:", &object->rgb_a, y + 12);
	ui_render_expandedproperty(FALSE, "Color B:", &object->rgb_b, y + 16);
	ui_render_expandedproperty(FALSE, "Position:", &object->pos, y + 20);
	ui_render_expandedproperty(FALSE, "Rotation:", &object->rot, y + 24);
	ui_render_expandedproperty(FALSE, "Scale:", &object->scale, y + 28);
	ui_render_expandedproperty(FALSE, "Object BBox VI:", &object->bbox_os.vi, y + 32);
	ui_render_expandedproperty(FALSE, "Object BBox VF:", &object->bbox_os.vf, y + 36);
	ui_render_expandedproperty(FALSE, "Axis BBox VI:", &object->bbox_ws.vi, y + 40);
	ui_render_expandedproperty(FALSE, "Axis BBox VF:", &object->bbox_ws.vf, y + 44);
	ui_render_expandedproperty(FALSE, "UVW Scale:", &object->uvw_scale, y + 48);
	ui_render_expandedproperty(FALSE, "UVW Pos:", &object->uvw_offset, y + 52);
	ui_render_text("Refrac:  Rough:   Opacity:", 1, y + 56, FALSE);
	ui_render_control_numberbox_float(1, y + 57, &object->refrac);
	ui_render_control_numberbox_float(10, y + 57, &object->roughness);
	ui_render_control_numberbox_float(19, y + 57, &object->opacity);
}

static void	ui_render_objectlist_object(SDL_Rect rect, t_u32 i, t_s32 height)
{
	t_bool		hover;

	if (rt.scene.objects[i].type &&
		rect.y + height >= rt.ui.objects.rect.y - TILE &&
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
}

void		ui_render_objectlist(void)
{
	t_s32		tmp;
	t_s32		add_height;
	SDL_Rect	rect;
	t_u32		i;

	rect = rt.ui.objects.rect;
	rect.h = 2;
	i = 0;
	while (i < rt.scene.object_amount)
	{
		tmp = rect.y;
		rect.y -= rt.ui.objects.scrollbar.scroll / TILE;
		add_height = (rt.ui.objects.expanded[i] ? OBJECT_PROPERTIES_H : 0);
		ui_render_objectlist_object(rect, i, add_height);
		rect.y = tmp;
		rect.y += 2 + add_height;
		++i;
	}
	rt.ui.objects.scrollbar.scroll_max = TILE * rect.y;
	if (rt.ui.objects.scrollbar.scroll > rt.ui.objects.scrollbar.scroll_max)
		rt.ui.objects.scrollbar.scroll = rt.ui.objects.scrollbar.scroll_max;
	if (rt.ui.objects.scrollbar.scroll_max >
		rt.ui.objects.scrollbar.scroll_view)
		ui_render_scrollbar(&rt.ui.objects.scrollbar);
}
