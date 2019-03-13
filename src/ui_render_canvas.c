/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_render_canvas.c                                 :+:      :+:    :+:   */
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

static void	ui_render_canvas_text(int y, char const *text, char *tmp)
{
	ui_render_text(text, UI_WIDTH_TILES + 2, y, FALSE);
	if (tmp)
	{
		ui_render_text(tmp, UI_WIDTH_TILES + 8, y, FALSE);
		free(tmp);
	}
}

void		ui_render_caminfo(t_camera *camera)
{
	ui_render_text("Camera", UI_WIDTH_TILES + 2, 1, FALSE);
	ui_render_canvas_text(2, "Mode: ", ft_u32_to_str(camera->mode));
	ui_render_canvas_text(4, "LAT-> ", ft_f32_to_str(camera->lat, 3));
	ui_render_canvas_text(5, "LON-> ", ft_f32_to_str(camera->lon, 3));
	ui_render_canvas_text(6, "Zoom: ", ft_f32_to_str(camera->zoom, 3));
	ui_render_canvas_text(7, "Tilt: ", ft_f32_to_str(camera->tilt_angle, 3));
	ui_render_canvas_text(9, "Anchor", cl_float3_to_str(&camera->anchor, 3));
	ui_render_canvas_text(10, "CamPos",
		cl_float3_to_str(&camera->relative_pos, 3));
}

void		ui_render_loading_bar(void)
{
	float	percent;
	char	*tmp;

	percent = g_rt.ocl.render_progress * 100.;
	tmp = ft_f32_to_str(percent, 3);
	tmp[ft_strlen(tmp) - 2] = ' ';
	tmp[ft_strlen(tmp) - 1] = '%';
	ui_render_text("Render", UI_WIDTH_TILES + 2, 11, FALSE);
	ui_render_text(tmp, UI_WIDTH_TILES + 8, 11, FALSE);
	if (tmp)
		free(tmp);
}
