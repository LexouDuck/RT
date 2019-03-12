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

void	ui_render_icon_object(t_object *object, t_s32 y)
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

void		ui_render_expandedproperties(t_object *object, t_s32 y)
{
	char		*tmp;

	ui_render_text("Primitive:", 1, y + 2, FALSE);
	ui_render_text(rt_get_str_primitive(object->type), 13, y + 2, FALSE);
	ui_render_text("\x12", 12, y + 2, FALSE);
	ui_render_text("\x13", 24, y + 2, FALSE);
	ui_render_text("Material:", 1, y + 4, FALSE);
	ui_render_text(rt_get_str_material(object->material), 13, y + 4, FALSE);
	ui_render_text("\x12", 12, y + 4, FALSE);
	ui_render_text("\x13", 24, y + 4, FALSE);
	ui_render_text("Pattern:", 1, y + 6, FALSE);
	ui_render_text(rt_get_str_pattern(object->pattern), 13, y + 6, FALSE);
	ui_render_text("\x12", 12, y + 6, FALSE);
	ui_render_text("\x13", 24, y + 6, FALSE);
	ui_render_text("Projection:", 1, y + 8, FALSE);
	ui_render_text(rt_get_str_projection(object->uvw_projection), 13, y + 8, FALSE);
	ui_render_text("\x12", 12, y + 8, FALSE);
	ui_render_text("\x13", 24, y + 8, FALSE);
	ui_render_text("Bump:", 1, y + 10, FALSE);
	ui_render_text(rt_get_str_bump(object->bump_type), 13, y + 10, FALSE);
	ui_render_text("\x12", 12, y + 10, FALSE);
	ui_render_text("\x13", 24, y + 10, FALSE);
	if ((tmp = ft_u32_to_hex(object->color_a)))
	{
		ui_render_text("Color A: #", 1, y + 12, FALSE);
		ui_render_text(tmp, 11, y + 12, FALSE);
		free(tmp);
	}
	ui_render_control_numberbox_float(1, y + 13, &object->rgb_a.x);
	ui_render_control_numberbox_float(10, y + 13, &object->rgb_a.y);
	ui_render_control_numberbox_float(19, y + 13, &object->rgb_a.z);
	if ((tmp = ft_u32_to_hex(object->color_b)))
	{
		ui_render_text("Color B: #", 1, y + 16, FALSE);
		ui_render_text(tmp, 11, y + 16, FALSE);
		free(tmp);
	}
	ui_render_control_numberbox_float(1, y + 17, &object->rgb_b.x);
	ui_render_control_numberbox_float(10, y + 17, &object->rgb_b.y);
	ui_render_control_numberbox_float(19, y + 17, &object->rgb_b.z);
	ui_render_text("Pos:", 1, y + 20, FALSE);
	ui_render_control_numberbox_float(1, y + 21, &object->pos.x);
	ui_render_control_numberbox_float(10, y + 21, &object->pos.y);
	ui_render_control_numberbox_float(19, y + 21, &object->pos.z);
	ui_render_text("Rot:", 1, y + 24, FALSE);
	ui_render_control_numberbox_float(1, y + 25, &object->rot.x);
	ui_render_control_numberbox_float(10, y + 25, &object->rot.y);
	ui_render_control_numberbox_float(19, y + 25, &object->rot.z);
	ui_render_text("Scale:", 1, y + 28, FALSE);
	ui_render_control_numberbox_float(1, y + 29, &object->scale.x);
	ui_render_control_numberbox_float(10, y + 29, &object->scale.y);
	ui_render_control_numberbox_float(19, y + 29, &object->scale.z);
	ui_render_text("Object BBox Corner VI:", 1, y + 32, FALSE);
	ui_render_control_numberbox_float(1, y + 33, &object->bbox_os.vi.x);
	ui_render_control_numberbox_float(10, y + 33, &object->bbox_os.vi.y);
	ui_render_control_numberbox_float(19, y + 33, &object->bbox_os.vi.z);
	ui_render_text("Object BBox Corner VF:", 1, y + 36, FALSE);
	ui_render_control_numberbox_float(1, y + 37, &object->bbox_os.vf.x);
	ui_render_control_numberbox_float(10, y + 37, &object->bbox_os.vf.y);
	ui_render_control_numberbox_float(19, y + 37, &object->bbox_os.vf.z);
	ui_render_text("World BBox Corner VI:", 1, y + 40, FALSE);
	ui_render_control_numberbox_float(1, y + 41, &object->bbox_ws.vi.x);
	ui_render_control_numberbox_float(10, y + 41, &object->bbox_ws.vi.y);
	ui_render_control_numberbox_float(19, y + 41, &object->bbox_ws.vi.z);
	ui_render_text("World BBox Corner VF:", 1, y + 44, FALSE);
	ui_render_control_numberbox_float(1, y + 45, &object->bbox_ws.vf.x);
	ui_render_control_numberbox_float(10, y + 45, &object->bbox_ws.vf.y);
	ui_render_control_numberbox_float(19, y + 45, &object->bbox_ws.vf.z);
	ui_render_text("UVW Scale:", 1, y + 48, FALSE);
	ui_render_control_numberbox_float( 1, y + 49, &object->uvw_scale.x);
	ui_render_control_numberbox_float(10, y + 49, &object->uvw_scale.y);
	ui_render_control_numberbox_float(19, y + 49, &object->uvw_scale.z);
	ui_render_text("UVW Offset:", 1, y + 52, FALSE);
	ui_render_control_numberbox_float( 1, y + 53, &object->uvw_offset.x);
	ui_render_control_numberbox_float(10, y + 53, &object->uvw_offset.y);
	ui_render_control_numberbox_float(19, y + 53, &object->uvw_offset.z);
	ui_render_text("Refrac:  Rough:   Opacity:", 1, y + 56, FALSE);
	ui_render_control_numberbox_float(1, y + 57, &object->refrac);
	ui_render_control_numberbox_float(10, y + 57, &object->roughness);
	ui_render_control_numberbox_float(19, y + 57, &object->opacity);
}

void	ui_render_objectlist(void)
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
		rect.y -= rt.ui.objects.scrollbar.scroll / TILE;
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
	rt.ui.objects.scrollbar.scroll_max = TILE * rect.y;
	if (rt.ui.objects.scrollbar.scroll > rt.ui.objects.scrollbar.scroll_max)
		rt.ui.objects.scrollbar.scroll = rt.ui.objects.scrollbar.scroll_max;
	if (rt.ui.objects.scrollbar.scroll_max > rt.ui.objects.scrollbar.scroll_view)
		ui_render_scrollbar(&rt.ui.objects.scrollbar);
}
