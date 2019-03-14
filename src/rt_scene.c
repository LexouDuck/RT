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

#include <math.h>

#include "libft_memory.h"
#include "libft_color.h"

#include "../rt.h"

void		remove_selected_objects(void)
{
	t_u32	i;

	i = 0;
	while (i < g_rt.scene.object_amount)
	{
		if (g_rt.ui.objects.selected[i])
		{
			ft_memcpy(&g_rt.scene.objects[i], &g_rt.scene.objects[i + 1],
				sizeof(t_object) * (g_rt.scene.object_amount - i));
			ft_memcpy(&g_rt.ui.objects.selected[i],
				&g_rt.ui.objects.selected[i + 1],
				sizeof(t_bool) * (g_rt.scene.object_amount - i));
			ft_memcpy(&g_rt.ui.objects.expanded[i],
				&g_rt.ui.objects.expanded[i + 1],
				sizeof(t_bool) * (g_rt.scene.object_amount - i));
			g_rt.scene.object_amount -= 1;
			ft_memclr(&g_rt.scene.objects[g_rt.scene.object_amount],
				sizeof(t_object));
			ft_memclr(&g_rt.ui.objects.selected[g_rt.scene.object_amount],
				sizeof(t_bool));
			ft_memclr(&g_rt.ui.objects.expanded[g_rt.scene.object_amount],
				sizeof(t_bool));
		}
		else
			++i;
	}
}

void		init_scene(void)
{
	g_rt.scene.bg_color = DEFAULT_BG_COLOR;
	g_rt.scene.bg_rgb = (cl_float3){{
		(DEFAULT_BG_COLOR & 0xFF0000) >> 16,
		(DEFAULT_BG_COLOR & 0x00FF00) >> 8,
		(DEFAULT_BG_COLOR & 0x0000FF) }};
	g_rt.scene.object_amount = 0;
	g_rt.scene.render_dist = DEFAULT_RENDER_DIST;
	g_rt.scene.bbox_ws.vi = (cl_float3){{
		-DEFAULT_RENDER_DIST,
		-DEFAULT_RENDER_DIST,
		-DEFAULT_RENDER_DIST }};
	g_rt.scene.bbox_ws.vf = (cl_float3){{
		DEFAULT_RENDER_DIST,
		DEFAULT_RENDER_DIST,
		DEFAULT_RENDER_DIST }};
	g_rt.scene.max_ray_depth = DEFAULT_MAX_RAY_DEPTH;
	g_rt.scene.mc_raysamp_size = DEFAULT_RAYSAMP_SIZE;
	g_rt.scene.work_dims = (t_work_array){g_rt.canvas_w, g_rt.canvas_h,
		((g_rt.scene.render_mode == RENDERMODE_MCPT) ?
			g_rt.scene.mc_raysamp_size : 1)};
	g_rt.scene.render_mode = DEFAULT_RENDER_MODE;
}

void		update_scene(void)
{
	g_rt.scene.bg_color = ft_color_argb32_set(0.,
		g_rt.scene.bg_rgb.x * 255.,
		g_rt.scene.bg_rgb.y * 255.,
		g_rt.scene.bg_rgb.z * 255.);
}

void		int_to_valid_pow_of_2(cl_uint *value, t_u32 max, t_u32 paired_value)
{
	t_float		lg2_f;
	t_u32		lg2_ui;

	if (*value > max)
		*value = max;
	else if (*value < 1)
		*value = 1;
	lg2_f = log2(*value);
	lg2_ui = round(lg2_f);
	*value = 0x1 << lg2_ui;
	if (g_rt.scene.mc_raysamp_size * g_rt.scene.max_ray_depth >=
										MAXIMUM_RENDER_PRODUCT)
		*value = MAXIMUM_RENDER_PRODUCT / paired_value;
}

void		ui_update_control_numberbox_int(cl_uint *value)
{
	if (value == &g_rt.ocl.gpu_platform_index)
	{
		if (*value >= g_rt.ocl.platform_amount)
			*value = g_rt.ocl.platform_amount - 1;
		opencl_freeall();
		opencl_init(g_rt.ocl.gpu_platform_index);
	}
	else if (value == &g_rt.scene.mc_raysamp_size)
	{
		int_to_valid_pow_of_2(value,
				MAXIMUM_RAYSAMP_SIZE, g_rt.scene.max_ray_depth);
		g_rt.scene.work_dims.z = *value;
	}
	else if (value == &g_rt.scene.max_ray_depth)
	{
		int_to_valid_pow_of_2(value,
				MAXIMUM_MAX_RAY_DEPTH, g_rt.scene.mc_raysamp_size);
	}
	g_rt.must_render = TRUE;
}
