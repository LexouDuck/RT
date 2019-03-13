/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_color.h"

#include "../rt.h"

void		remove_selected_objects(void)
{
	t_u32	i;

	i = 0;
	while (i < rt.scene.object_amount)
	{
		if (rt.ui.objects.selected[i])
		{
			ft_memcpy(&rt.scene.objects[i], &rt.scene.objects[i + 1],
				sizeof(t_object) * (rt.scene.object_amount - i));
			ft_memcpy(&rt.ui.objects.selected[i], &rt.ui.objects.selected[i + 1],
				sizeof(t_bool) * (rt.scene.object_amount - i));
			ft_memcpy(&rt.ui.objects.expanded[i], &rt.ui.objects.expanded[i + 1],
				sizeof(t_bool) * (rt.scene.object_amount - i));
			rt.scene.object_amount -= 1;
			ft_memclr(&rt.scene.objects[rt.scene.object_amount],
				sizeof(t_object));
			ft_memclr(&rt.ui.objects.selected[rt.scene.object_amount],
				sizeof(t_bool));
			ft_memclr(&rt.ui.objects.expanded[rt.scene.object_amount],
				sizeof(t_bool));
		}
		++i;
	}
}

void		init_scene(void)
{
	rt.scene.bg_color = DEFAULT_BG_COLOR;
	rt.scene.bg_rgb = (cl_float3){{
		(DEFAULT_BG_COLOR & 0xFF0000) >> 16,
		(DEFAULT_BG_COLOR & 0x00FF00) >> 8,
		(DEFAULT_BG_COLOR & 0x0000FF) }};
	rt.scene.object_amount = 0;
	rt.scene.render_dist = DEFAULT_RENDER_DIST;
	rt.scene.bbox_ws.vi = (cl_float3){{
		-DEFAULT_RENDER_DIST,
		-DEFAULT_RENDER_DIST,
		-DEFAULT_RENDER_DIST }};
	rt.scene.bbox_ws.vf = (cl_float3){{
		DEFAULT_RENDER_DIST,
		DEFAULT_RENDER_DIST,
		DEFAULT_RENDER_DIST }};
	rt.scene.max_ray_depth = DEFAULT_MAX_RAY_DEPTH;
	rt.scene.mc_raysamp_size = DEFAULT_RAYSAMP_SIZE;
	rt.scene.work_dim[0] = rt.canvas_w;
	rt.scene.work_dim[1] = rt.canvas_h;
	rt.scene.render_mode = DEFAULT_RENDER_MODE;
}

void		update_scene(void)
{
	rt.scene.bg_color = ft_color_argb32_set(0.,
		rt.scene.bg_rgb.x * 255.,
		rt.scene.bg_rgb.y * 255.,
		rt.scene.bg_rgb.z * 255.);
}
