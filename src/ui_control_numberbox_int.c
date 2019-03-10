/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_control_numberbox_int.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:03:10 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft_string.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

static void	ui_change_control_numberbox_int(cl_uint *value)
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
		if (*value > MAXIMUM_RAYSAMP_SIZE)
			*value = MAXIMUM_RAYSAMP_SIZE;
		else if (*value < 1)
			*value = 1;
	}
	else if (value == &rt.scene.max_ray_depth)
	{
		if (*value > MAXIMUM_MAX_RAY_DEPTH)
			*value = MAXIMUM_MAX_RAY_DEPTH;
		else if (*value < 1)
			*value = 1;
	}
	rt.must_render = TRUE;
}

void	ui_leave_control_numberbox_int(t_textinput *textinput)
{
	cl_uint	*value;

	if (textinput->value && rt.ui.current_textinput.value_changed)
	{
		value = (cl_uint *)textinput->value;
		*value = textinput->input ? ft_str_to_s32(textinput->input) : 0;
		ui_change_control_numberbox_int(value);
	}
	if (textinput->input)
		free(textinput->input);
	textinput->input = NULL;
	if (textinput->type)
	{
		textinput->type = texttype_none;
		textinput->value = NULL;
		SDL_StopTextInput();
	}
}

void	ui_keypress_control_numberbox_int(t_textinput *textinput, t_bool up)
{
	cl_uint *value;

	value = (cl_uint *)textinput->value;
	if (up)
		*value += 1;
	else
		*value -= 1;
	rt.must_render = TRUE;
	ui_leave_control_numberbox_int(textinput);
	textinput->type = texttype_number_int;
	textinput->input = ft_s32_to_str(*value);
	textinput->value = (void *)value;
	rt.ui.current_textinput.value_changed = FALSE;
	SDL_StartTextInput();
}

t_bool	ui_mouse_control_numberbox_int(t_textinput *textinput, cl_uint *value, int x, int y)
{
	static SDL_Rect	rect = { 0, 0, 9 * TILE, 3 * TILE };
	static SDL_Rect	button = { 0, 0, 2 * TILE, 1 * TILE };

	rect.x = x * TILE;
	rect.y = y * TILE;
	if (SDL_PointInRect(&rt.input.mouse, &rect))
	{
		button.x = rect.x + rect.w - button.w;
		button.y = rect.y;
		if (SDL_PointInRect(&rt.input.mouse, &button))
		{
			*value += 1;
			ui_change_control_numberbox_int(value);
		}
		else if ((button.y += 2 * TILE) && SDL_PointInRect(&rt.input.mouse, &button))
		{
			*value -= 1;
			ui_change_control_numberbox_int(value);
		}
		else
		{
			textinput->type = texttype_number_int;
			textinput->input = ft_s32_to_str(*value);
			textinput->value = (void *)value;
			rt.ui.current_textinput.value_changed = FALSE;
			SDL_StartTextInput();
		}
		return (TRUE);
	}
	return (FALSE);
}

void	ui_render_control_numberbox_int(int x, int y, cl_uint *value)
{
	static const size_t	str_max_length = 7;
	static SDL_Rect		rect = { 0, 0, 9, 3 };
	char				*str;

	rect.x = x;
	rect.y = y;
	ui_render_rect(rect, (value == rt.ui.current_textinput.value));
	if (value == rt.ui.current_textinput.value)
	{
		ui_render_text(rt.ui.current_textinput.input, rect.x + 1, rect.y + 1, FALSE);
	}
	else if ((str = ft_s32_to_str(*value)))
	{
		if (ft_strlen(str) > str_max_length)
			str[str_max_length] = '\0';
		ui_render_text(str, rect.x + 1, rect.y + 1, FALSE);
		free(str);
	}
	ui_render_text("\x10", rect.x + rect.w - 2, rect.y + 0, TRUE);
	ui_render_text("\x11", rect.x + rect.w - 2, rect.y + 2, TRUE);
}