/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

/*
**	ft_putstr("MOUSE PRESSED: ");
**	ft_putstr(ft_itoa_hex((t_u32)button, "0x"));
**	ft_putstr(" | x:"); ft_putstr(ft_itoa(x));
**	ft_putstr(", y:"); ft_putendl(ft_itoa(y));
*/

static int	event_mouse_press(int button, int x, int y, void *param)
{
	t_mlx		*mlx;
	t_camera	*camera;

	mlx = (t_mlx *)param;
	camera = mlx->rtv1->camera;
	if (button == MOUSE_SCROLL_UP ||
		button == MOUSE_SCROLL_DOWN)
	{
		camera->zoom *= (button == MOUSE_SCROLL_UP) ? 0.9 : 1.1;
		if (camera->zoom < 1)
			camera->zoom = 1;
	}
	else if (button == MOUSE_L_CLICK)
		camera->mode = CAMERA_PAN;
	else if (button == MOUSE_M_CLICK)
		camera->mode = CAMERA_ZOOM;
	else if (button == MOUSE_R_CLICK)
		camera->mode = CAMERA_ROTATE;
	render(mlx, camera);
	return ((x || y) ? OK : OK);
}

/*
**	ft_putstr("MOUSE RELEASED:");
**	ft_putstr(ft_itoa_hex((t_u32)button, "0x"));
**	ft_putstr(" | x:"); ft_putstr(ft_itoa(x));
**	ft_putstr(", y:"); ft_putendl(ft_itoa(y));
*/

static int	event_mouse_release(int button, int x, int y, void *param)
{
	t_mlx		*mlx;
	t_camera	*camera;

	mlx = (t_mlx *)param;
	camera = mlx->rtv1->camera;
	camera->mode = CAMERA_NONE;
	return ((button || x || y) ? OK : OK);
}

static int	event_mouse_move(int x, int y, void *param)
{
	static int	old_x = 0;
	static int	old_y = 0;
	t_mlx		*mlx;
	t_camera	*camera;
	t_vector	mouse;

	mlx = (t_mlx *)param;
	camera = mlx->rtv1->camera;
	mouse.x = (float)(x - old_x) * 0.05;
	mouse.y = (float)(y - old_y) * 0.05;
	if (camera->mode != CAMERA_NONE)
	{
		if (camera->mode == CAMERA_ZOOM)
			camera_zoom_tilt(camera, mouse.x, mouse.y);
		else if (camera->mode == CAMERA_ROTATE)
			camera_rotate(camera, mouse.x, mouse.y);
		else if (camera->mode == CAMERA_PAN)
			camera_pan(camera, mouse.x, mouse.y * 0.5);
		if (x != old_x || y != old_y)
			render(mlx, camera);
	}
	old_x = x;
	old_y = y;
	return (OK);
}

/*
**	ft_putstr("KEY PRESSED: ");
**	ft_putendl(ft_itoa_hex((t_u32)key, "0x"));
*/

static int	event_key(int key, void *param)
{
	t_mlx		*mlx;
	t_camera	*camera;

	mlx = (t_mlx *)param;
	camera = mlx->rtv1->camera;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(OK);
	}
	else if (key == KEY_HOME)
		camera->render += (camera->render & 0b100) ? -0b100 : 0b100;
	else if (key == KEY_END)
		camera->render += (camera->render & 0b010) ? -0b010 : 0b010;
	else if (key == KEY_DELETE)
		camera->render += (camera->render & 0b001) ? -0b001 : 0b001;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		camera->anchor.x += (key == KEY_LEFT) ? -1 : 1;
	else if (key == KEY_DOWN || key == KEY_UP)
		camera->anchor.z += (key == KEY_UP) ? -1 : 1;
	else if (key == KEY_PAGE_DN || key == KEY_PAGE_UP)
		camera->anchor.y += (key == KEY_PAGE_DN) ? -1 : 1;
	render(mlx, camera);
	return (OK);
}

int			setup_events(t_mlx *mlx)
{
	int event;
	int	mask;

	mlx_expose_hook(mlx->win_ptr, handle_expose, mlx);
	mlx_key_hook(mlx->win_ptr, event_key, mlx);
	mask = 0;
	mask |= MASK_POINTERMOTION;
	mask |= MASK_BUTTON1MOTION;
	mask |= MASK_BUTTON2MOTION;
	mask |= MASK_BUTTON3MOTION;
	event = EVENT_MOTIONNOTIFY;
	mlx_hook(mlx->win_ptr, event, mask, event_mouse_move, mlx);
	mask = MASK_BUTTONPRESS;
	event = EVENT_BUTTONPRESS;
	mlx_hook(mlx->win_ptr, event, mask, event_mouse_press, mlx);
	mask = MASK_BUTTONRELEASE;
	event = EVENT_BUTTONRELEASE;
	mlx_hook(mlx->win_ptr, event, mask, event_mouse_release, mlx);
	return (OK);
}
