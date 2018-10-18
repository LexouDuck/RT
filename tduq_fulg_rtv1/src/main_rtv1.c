/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rtv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:27:46 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 16:30:12 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			exit_error(char *e_msg, int e_no)
{
	int		i;

	if (e_no == 0)
	{
		i = write(2, e_msg, ft_strlen(e_msg));
		i += write(2, "\n", 1);
		exit(i);
	}
	else
		perror(e_msg);
	exit(e_no);
}

/*
** Bits per pixel (32, each color is an int) are immediately converted to
** bytes per pixel.
**
** Anchor is which point of the complex plane is the center of the window.
*/

static void		init_mlx(t_control *ctrl)
{
	if (!(ctrl->mlx_ptr = mlx_init()))
		exit_error("could not init mlx_ptr", 0);
	if (!(ctrl->win_ptr = mlx_new_window(ctrl->mlx_ptr,
				REN_W, REN_H, "RTv1")))
		exit_error("could not init win_ptr", 0);
	if (!(ctrl->img_ptr = mlx_new_image(ctrl->mlx_ptr, REN_W, REN_H)))
		exit_error("could not init img_ptr", 0);
	if (!(ctrl->img_data = mlx_get_data_addr(ctrl->img_ptr, &(ctrl->img_bpp),
										&(ctrl->img_bpl), &(ctrl->endian))))
		exit_error("could not retrieve img data ptr and other info", 0);
	ctrl->img_bpp = ctrl->img_bpp / 8;
	ctrl->img_pixel_nb = REN_W * REN_H;
	ctrl->img_bytelen = ctrl->img_bpp * ctrl->img_pixel_nb;
	ctrl->debug = 1;
}

int				main(int argc, char **argv)
{
	t_control	ctrl;

	if (argc != 2)
		exit_error("rtv1 usage: \"./rtv1 [filepath]\"", 0);
	init_mlx(&ctrl);
	vec3_set(ctrl.cam.polar_pos, 10., HALF_PI, HALF_PI);
	ctrl.spotlst_len = 0;
	ctrl.objlst_len = 0;
	ctrl.show_diffuse = TRUE;
	ctrl.show_specular = TRUE;
	ctrl.cam.hrz_fov = INIT_FOV;
	ctrl.render_dist = 1.e+6;
	read_rt_file(&ctrl, argv[1]);
	render(&ctrl);
	mlx_key_hook(ctrl.win_ptr, handle_key, &ctrl);
	mlx_expose_hook(ctrl.win_ptr, handle_redraw, &ctrl);
	mlx_loop(ctrl.mlx_ptr);
	return (0);
}
