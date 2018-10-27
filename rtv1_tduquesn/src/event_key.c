/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 20:49:10 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/05 07:58:46 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_bool		handle_key_helper(t_control *ctrl, int key)
{
	if (key == KEY_PAGE_DN)
		ctrl->cam.polar_pos[0] *= 1.1;
	else if (key == KEY_PAGE_UP)
		ctrl->cam.polar_pos[0] *= 0.9;
	else if (key == KEY_LEFT)
		ctrl->cam.polar_pos[1] -= 0.2;
	else if (key == KEY_RIGHT)
		ctrl->cam.polar_pos[1] += 0.2;
	else if (key == KEY_DOWN && ctrl->cam.polar_pos[2] - 0.1 > -0.00001)
		ctrl->cam.polar_pos[2] -= 0.1;
	else if (key == KEY_UP && ctrl->cam.polar_pos[2] + 0.1 < PI + 0.00001)
		ctrl->cam.polar_pos[2] += 0.1;
	else if (key == KEY_J && ctrl->cam.hrz_fov - 0.05 > 0.)
		ctrl->cam.hrz_fov -= 0.05;
	else if (key == KEY_K && ctrl->cam.hrz_fov + 0.05 < TAU)
		ctrl->cam.hrz_fov += 0.05;
	else if (key == KEY_D)
		ctrl->show_diffuse = !(ctrl->show_diffuse);
	else if (key == KEY_S)
		ctrl->show_specular = !(ctrl->show_specular);
	else
		return (FALSE);
	return (TRUE);
}

int			handle_key(int key, void *param)
{
	t_control			*ctrl;

	ctrl = (t_control *)param;
	if (key == KEY_ESC)
		exit_error("Software closing.", 0);
	else if (key == KEY_LCTRL)
		ctrl->debug = !(ctrl->debug);
	else if (key == KEY_NUMPAD_4)
		ctrl->cam.anchor[0] -= 0.5;
	else if (key == KEY_NUMPAD_6)
		ctrl->cam.anchor[0] += 0.5;
	else if (key == KEY_NUMPAD_5)
		ctrl->cam.anchor[1] -= 0.5;
	else if (key == KEY_NUMPAD_8)
		ctrl->cam.anchor[1] += 0.5;
	else if (key == KEY_NUMPAD_2)
		ctrl->cam.anchor[2] -= 0.5;
	else if (key == KEY_NUMPAD_0)
		ctrl->cam.anchor[2] += 0.5;
	else if (handle_key_helper(ctrl, key))
		;
	else
		return (1);
	render(ctrl);
	return (0);
}
