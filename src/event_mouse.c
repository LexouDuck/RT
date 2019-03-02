/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:08 by hbruvry          ###   ########.fr       */
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
		t_bool mouse_in_objectlist;
		rt.ui.objects.rect.w += 2;
		mouse_in_objectlist = SDL_PointInRect(&rt.input.mouse_tile, &rt.ui.objects.rect);
		rt.ui.objects.rect.w -= 2;
		if (mouse_in_objectlist && (rt.ui.objects.scrollbar.scroll > 0 ||
			rt.ui.objects.scrollbar.scroll_max > rt.ui.objects.scrollbar.scroll_view))
			ui_scrollbar_setscroll(&rt.ui.objects.scrollbar, event->wheel.y * -10);
		else
		{
			if (event->wheel.y > 0)
				camera->zoom *= 0.9;
			if (event->wheel.y < 0)
				camera->zoom *= 1.1;
			if (camera->zoom < EPS)
				camera->zoom = EPS;
			camera_update(camera);
			rt.must_render = TRUE;
		}
	}
}

void	event_mouse_press(SDL_Event *event)
{
	t_camera	*camera;

	camera = &rt.scene.camera;
	if (event->button.x < UI_WIDTH)
	{
		if (event->button.button == SDL_BUTTON_LEFT &&
			(rt.ui.objects.scrollbar.scroll_max > rt.ui.objects.scrollbar.scroll_view))
			ui_mouse_scrollbar();
		return ;
	}
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

	rt.ui.objects.scrollbar.clicked = scrollclick_none;
	camera = &rt.scene.camera;
	if (camera->mode)
		rt.must_render = TRUE;
	camera->mode = CAMERA_MODE_NONE;
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (rt.ui.current_textinput.type)
		{
			if (rt.ui.current_textinput.type == texttype_number_float)
				ui_leave_control_numberbox(&rt.ui.current_textinput);
			else if (rt.ui.current_textinput.type == texttype_text)
				ui_leave_control_textbox(&rt.ui.current_textinput);
		}
		if (rt.ui.current_prompt.name)
			ui_mouse_prompt();
		else
		{
			if (rt.ui.menubar.selection >= 0)
				ui_mouse_dropdown(&rt.ui.dropdowns[rt.ui.menubar.selection]);
			else
			{
				ui_mouse_objectlist();
				ui_mouse_menu();
			}
			ui_mouse_menubar();
		}
	}
	if (SDL_CaptureMouse(FALSE))
		debug_output_error("Unable to release the mouse cursor input.", TRUE);
}

void	event_mouse_motion(SDL_Event *event)
{
	float		motion_x;
	float		motion_y;
	t_camera	*camera;

	camera = &rt.scene.camera;
	if (rt.ui.objects.scrollbar.clicked == scrollclick_bar)
	{
		t_scrollbar	*scrollbar;
		t_f32		ratio;
		scrollbar = &rt.ui.objects.scrollbar;
		ratio = ((t_f32)scrollbar->scroll_max / (t_f32)scrollbar->bar.h);
		ui_scrollbar_setscroll(scrollbar, event->motion.yrel * ratio);
	}
	else if (camera->mode != CAMERA_MODE_NONE &&
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
