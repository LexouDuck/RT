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
			ft_memcpy(&rt.ui.objects.selected[i],
				&rt.ui.objects.selected[i + 1],
				sizeof(t_bool) * (rt.scene.object_amount - i));
			ft_memcpy(&rt.ui.objects.expanded[i],
				&rt.ui.objects.expanded[i + 1],
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
	rt.scene.work_dims = (t_work_array){rt.canvas_w, rt.canvas_h,
		((rt.scene.render_mode == RENDERMODE_MCPT) ?
			rt.scene.mc_raysamp_size : 1)};
	rt.scene.render_mode = DEFAULT_RENDER_MODE;
}

void		update_scene(void)
{
	rt.scene.bg_color = ft_color_argb32_set(0.,
		rt.scene.bg_rgb.x * 255.,
		rt.scene.bg_rgb.y * 255.,
		rt.scene.bg_rgb.z * 255.);
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
	if (rt.scene.mc_raysamp_size * rt.scene.max_ray_depth >=
										MAXIMUM_RENDER_PRODUCT)
		*value = MAXIMUM_RENDER_PRODUCT / paired_value;
}

void		ui_update_control_numberbox_int(cl_uint *value)
{
	if (value == &rt.ocl.gpu_platform_index)
	{
		if (*value >= rt.ocl.platform_amount)
			*value = rt.ocl.platform_amount - 1;
		opencl_freeall();
		opencl_init(rt.ocl.gpu_platform_index);
	}
	else if (value == &rt.scene.mc_raysamp_size)
	{
		int_to_valid_pow_of_2(value,
				MAXIMUM_RAYSAMP_SIZE, rt.scene.max_ray_depth);
		rt.scene.work_dims.z = *value;
	}
	else if (value == &rt.scene.max_ray_depth)
	{
		int_to_valid_pow_of_2(value,
				MAXIMUM_MAX_RAY_DEPTH, rt.scene.mc_raysamp_size);
	}
	rt.must_render = TRUE;
}
