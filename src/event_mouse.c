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

void		event_mouse_wheel(SDL_Event *event)
{
	t_bool mouse_in_objectlist;

	if (event->wheel.y == 0)
		return ;
	g_rt.ui.objects.rect.w += 2;
	mouse_in_objectlist = SDL_PointInRect(
		&g_rt.input.mouse_tile, &g_rt.ui.objects.rect);
	g_rt.ui.objects.rect.w -= 2;
	if (mouse_in_objectlist && (g_rt.ui.objects.scrollbar.scroll > 0 ||
		g_rt.ui.objects.scrollbar.scroll_max >
		g_rt.ui.objects.scrollbar.scroll_view))
		ui_scrollbar_setscroll(&g_rt.ui.objects.scrollbar,
			event->wheel.y * -10);
	else
	{
		if (event->wheel.y > 0)
			g_rt.scene.camera.zoom *= 0.9;
		if (event->wheel.y < 0)
			g_rt.scene.camera.zoom *= 1.1;
		if (g_rt.scene.camera.zoom < EPS)
			g_rt.scene.camera.zoom = EPS;
		camera_update(&g_rt.scene.camera);
		g_rt.must_render = TRUE;
	}
	return ;
}

void		event_mouse_press(SDL_Event *event)
{
	if (event->button.x < UI_WIDTH)
	{
		if (event->button.button == SDL_BUTTON_LEFT && (
			g_rt.ui.objects.scrollbar.scroll_max >
			g_rt.ui.objects.scrollbar.scroll_view))
			ui_mouse_scrollbar();
		return ;
	}
	else if (event->button.button == SDL_BUTTON_LEFT)
		g_rt.scene.camera.mode = CAMERA_MODE_PAN;
	else if (event->button.button == SDL_BUTTON_MIDDLE)
		g_rt.scene.camera.mode = CAMERA_MODE_TILT;
	else if (event->button.button == SDL_BUTTON_RIGHT)
		g_rt.scene.camera.mode = CAMERA_MODE_ROTATE;
	if (g_rt.scene.camera.mode && SDL_CaptureMouse(TRUE))
		debug_output_error("Unable to capture the mouse cursor input.", TRUE);
	return ;
}

static void	event_mouse_release_textinput(void)
{
	if (g_rt.ui.current_textinput.type)
	{
		if (g_rt.ui.current_textinput.type == texttype_text)
			ui_leave_control_textbox(&g_rt.ui.current_textinput);
		else if (g_rt.ui.current_textinput.type == texttype_number_int)
			ui_leave_control_numberbox_int(&g_rt.ui.current_textinput);
		else if (g_rt.ui.current_textinput.type == texttype_number_float)
			ui_leave_control_numberbox_float(&g_rt.ui.current_textinput);
	}
	return ;
}

void		event_mouse_release(SDL_Event *event)
{
	g_rt.ui.objects.scrollbar.clicked = scrollclick_none;
	if (g_rt.scene.camera.mode)
		g_rt.must_render = TRUE;
	g_rt.scene.camera.mode = CAMERA_MODE_NONE;
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		event_mouse_release_textinput();
		if (g_rt.ui.current_prompt.name)
			ui_mouse_prompt();
		else
		{
			if (g_rt.ui.menubar.selection >= 0)
				ui_mouse_dropdown(
					&g_rt.ui.dropdowns[g_rt.ui.menubar.selection]);
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
	return ;
}

void		event_mouse_motion(SDL_Event *event)
{
	t_scrollbar	*scrollbar;
	t_f32		ratio;

	if (g_rt.ui.objects.scrollbar.clicked == scrollclick_bar)
	{
		scrollbar = &g_rt.ui.objects.scrollbar;
		ratio = ((t_f32)scrollbar->scroll_max / (t_f32)scrollbar->bar.h);
		ui_scrollbar_setscroll(scrollbar, event->motion.yrel * ratio);
	}
	else if (g_rt.scene.camera.mode != CAMERA_MODE_NONE &&
		(event->motion.xrel || event->motion.yrel))
	{
		if (g_rt.scene.camera.mode == CAMERA_MODE_TILT)
			camera_zoom_tilt(&g_rt.scene.camera,
				(event->motion.xrel) * 0.1, (event->motion.yrel) * 0.1);
		else if (g_rt.scene.camera.mode == CAMERA_MODE_ROTATE)
			camera_rotate(&g_rt.scene.camera,
				(event->motion.xrel) * 0.1, (event->motion.yrel) * 0.1);
		else if (g_rt.scene.camera.mode == CAMERA_MODE_PAN)
			camera_pan(&g_rt.scene.camera,
				(event->motion.xrel) * 0.1, (event->motion.yrel) * 0.1);
		camera_update(&g_rt.scene.camera);
		g_rt.must_render = TRUE;
	}
	return ;
}
