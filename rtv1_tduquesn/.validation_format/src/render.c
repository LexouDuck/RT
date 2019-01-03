/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 00:08:48 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/05 07:45:30 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		show_debug_info(t_control *ctrl)
{
	char	*str;

	str = NULL;
	ft_asprintf(&str, "anchr: (x : %7.4f, y : %7.4f, z : %7.4f)",
		ctrl->cam.anchor[0], ctrl->cam.anchor[1], ctrl->cam.anchor[2]);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 20, 20, WHITE, str);
	ft_strdel(&str);
	ft_asprintf(&str, "polar: (nm: %7.4f, ln: %7.4f, lt: %7.4f)",
		ctrl->cam.polar_pos[0], ctrl->cam.polar_pos[1], ctrl->cam.polar_pos[2]);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 20, 40, WHITE, str);
	ft_strdel(&str);
	ft_asprintf(&str, "world: (x : %7.4f, y : %7.4f, z : %7.4f)",
		ctrl->cam.world_pos[0], ctrl->cam.world_pos[1], ctrl->cam.world_pos[2]);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 20, 60, WHITE, str);
	ft_strdel(&str);
}

int				handle_redraw(void *param)
{
	t_control	*ctrl;

	ctrl = (t_control *)param;
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	if (ctrl->debug)
		show_debug_info(ctrl);
	return (0);
}

void			render(t_control *ctrl)
{
	mlximg_fill(ctrl, BG_COLOR);
	ctrl->cam = init_cam(ctrl->cam.polar_pos, ctrl->cam.anchor,
								ctrl->cam.hrz_fov);
	cast_rays(ctrl);
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	if (ctrl->debug)
		show_debug_info(ctrl);
}
