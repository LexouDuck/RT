/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"
#include "event.h"
#include "ui.h"

void	event_mouse_wheel(SDL_Event *event)
{
	t_camera	*camera;

	camera = &rt.scene.camera;
	if (event->wheel.y)
	{
		if (event->wheel.y > 0)
			camera->zoom *= 0.9;
		if (event->wheel.y < 0)
			camera->zoom *= 1.1;
		if (camera->zoom < 1)
			camera->zoom = 1;
		camera_update(camera);
		rt.must_render = TRUE;
	}
}

void	event_mouse_press(SDL_Event *event)
{
	t_camera	*camera;

	camera = &rt.scene.camera;
	if (event->button.x < UI_WIDTH)
		return ;
	else if (event->button.button == SDL_BUTTON_LEFT)
		camera->mode = CAMERA_MODE_PAN;
	else if (event->button.button == SDL_BUTTON_MIDDLE)
		camera->mode = CAMERA_MODE_TILT;
	else if (event->button.button == SDL_BUTTON_RIGHT)
		camera->mode = CAMERA_MODE_ROTATE;
	if (camera->mode && SDL_CaptureMouse(TRUE))
		debug_output_error("Unable to capture the mouse cursor input.", TRUE);
}

void	event_mouse_release(SDL_Event *event)
{
	t_camera	*camera;

	camera = &rt.scene.camera;
	if (camera->mode)
		rt.must_render = TRUE;
	camera->mode = CAMERA_MODE_NONE;
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (rt.ui.menubar.selection == -1)
			ui_mouse_objectlist();
		else
			ui_mouse_dropdown(&rt.ui.dropdowns[rt.ui.menubar.selection]);
		ui_mouse_menubar();
	}
	if (camera->mode && SDL_CaptureMouse(FALSE))
		debug_output_error("Unable to release the mouse cursor input.", TRUE);
}

void	event_mouse_motion(SDL_Event *event)
{
	float		motion_x;
	float		motion_y;
	t_camera	*camera;

	camera = &rt.scene.camera;
	if (camera->mode != CAMERA_MODE_NONE &&
		(event->motion.xrel || event->motion.yrel))
	{
		motion_x = (float)(event->motion.xrel) * 0.1;
		motion_y = (float)(event->motion.yrel) * 0.1;
		if (camera->mode == CAMERA_MODE_TILT)
			camera_zoom_tilt(camera, motion_x, motion_y);
		else if (camera->mode == CAMERA_MODE_ROTATE)
			camera_rotate(camera, motion_x, motion_y);
		else if (camera->mode == CAMERA_MODE_PAN)
			camera_pan(camera, motion_x, motion_y);
		camera_update(camera);
		rt.must_render = TRUE;
	}
}
