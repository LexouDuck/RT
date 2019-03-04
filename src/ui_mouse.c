/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:47:32 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

static t_bool	ui_mouse_menu_rendermode(t_rendermode *rendermode)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.y = 3;
	rect.x = 14;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*rendermode = ((int)*rendermode == 0) ? (RENDER_MODES - 1) : ((int)*rendermode - 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 27;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*rendermode = ((int)*rendermode == (RENDER_MODES - 1)) ? 0 : ((int)*rendermode + 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ui_mouse_menu_cameramodel(t_camera_model *cameramodel)
{
	static SDL_Rect	rect = { 0, 0, 1, 1 };

	rect.y = 5;
	rect.x = 14;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*cameramodel = ((int)*cameramodel == 0) ? (CAMERA_MODELS - 1) : ((int)*cameramodel - 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	rect.x = 27;
	if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
	{
		*cameramodel = ((int)*cameramodel == (CAMERA_MODELS - 1)) ? 0 : ((int)*cameramodel + 1);
		rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void	ui_mouse_menu(void)
{
	if (ui_mouse_menu_rendermode(&rt.scene.render_mode))
		return ;
	if (ui_mouse_menu_cameramodel(&rt.scene.camera.model))
		return ;
	ui_mouse_control_numberbox(&rt.ui.current_textinput, &rt.scene.camera.hrz_fov,     1, 6);
	ui_mouse_control_numberbox(&rt.ui.current_textinput, &rt.scene.camera.aperture,   10, 6);
	ui_mouse_control_numberbox(&rt.ui.current_textinput, &rt.scene.camera.focal_dist, 19, 6);
}

void	ui_mouse_menubar(void)
{
	t_bool		collided;
	SDL_Rect	rect;
	t_s8		i;

	collided = FALSE;
	i = -1;
	while (++i < MENUBAR_ITEMS)
	{
		rect = rt.ui.menubar.item_hitbox[i];
		if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
		{
			rt.ui.menubar.selection = i;
			collided = TRUE;
		}
	}
	if (!collided)
		rt.ui.menubar.selection = -1;
}

void	ui_mouse_dropdown(t_menu *dropdown)
{
	t_bool		collided;
	SDL_Rect	rect;
	t_s8		i;

	if (dropdown && rt.ui.menubar.selection != -1)
	{
		collided = FALSE;
		i = -1;
		while (++i < dropdown->item_amount)
		{
			rect = dropdown->item_hitbox[i];
			if (SDL_PointInRect(&rt.input.mouse_tile, &rect))
			{
				if (dropdown->item_action[i])
					dropdown->item_action[i]();
				collided = TRUE;
			}
		}
		if (!collided)
			dropdown->selection = -1;
	}
}
