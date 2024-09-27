/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_control_numberbox_float.c                       :+:      :+:    :+:   */
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

void	ui_leave_control_numberbox_float(t_textinput *textinput)
{
	cl_float	*value;

	if (textinput->value && g_rt.ui.current_textinput.value_changed)
	{
		value = (cl_float *)textinput->value;
		*value = textinput->input ? ft_str_to_f32(textinput->input) : 0;
		if (isnan(*value))
			*value = 0;
		g_rt.must_render = TRUE;
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

void	ui_keypress_control_numberbox_float(t_textinput *textinput, t_bool up)
{
	cl_float *value;

	value = (cl_float *)textinput->value;
	if (up)
		*value += 1.0;
	else
		*value -= 1.0;
	g_rt.must_render = TRUE;
	ui_leave_control_numberbox_float(textinput);
	textinput->type = texttype_number_float;
	textinput->input = ft_f32_to_str(*value, 4);
	textinput->value = (void *)value;
	g_rt.ui.current_textinput.value_changed = FALSE;
	SDL_StartTextInput();
}

t_bool	ui_mouse_control_numberbox_increment_float(SDL_Rect button
		, cl_float *value)
{
	if (SDL_PointInRect(&g_rt.input.mouse, &button))
	{
		*value += 0.500;
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	button.y += 2 * TILE;
	if (SDL_PointInRect(&g_rt.input.mouse, &button))
	{
		*value -= 0.500;
		g_rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ui_mouse_control_numberbox_float(t_textinput *textinput,
	cl_float *value, int x, int y)
{
	static SDL_Rect	rect = { 0, 0, 9 * TILE, 3 * TILE };
	static SDL_Rect	button = { 0, 0, 2 * TILE, 1 * TILE };

	rect.x = x * TILE;
	rect.y = y * TILE;
	if (SDL_PointInRect(&g_rt.input.mouse, &rect))
	{
		button.x = rect.x + rect.w - button.w;
		button.y = rect.y;
		if (ui_mouse_control_numberbox_increment_float(button, value))
			return (TRUE);
		textinput->type = texttype_number_float;
		textinput->input = ft_f32_to_str(*value, 4);
		textinput->value = (void *)value;
		g_rt.ui.current_textinput.value_changed = FALSE;
		SDL_StartTextInput();
		return (TRUE);
	}
	return (FALSE);
}

void	ui_render_control_numberbox_float(int x, int y, cl_float *value)
{
	static const size_t	str_max_length = 7;
	static SDL_Rect		rect = { 0, 0, 9, 3 };
	char				*str;

	rect.x = x;
	rect.y = y;
	ui_render_rect(rect, (value == g_rt.ui.current_textinput.value));
	if (value == g_rt.ui.current_textinput.value)
	{
		ui_render_text(g_rt.ui.current_textinput.input,
			rect.x + 1, rect.y + 1, FALSE);
	}
	else if ((str = ft_f32_to_str(*value, 4)))
	{
		if (ft_strlen(str) > str_max_length)
			str[str_max_length] = '\0';
		ui_render_text(str, rect.x + 1, rect.y + 1, FALSE);
		free(str);
	}
	ui_render_text("\x10", rect.x + rect.w - 2, rect.y + 0, TRUE);
	ui_render_text("\x11", rect.x + rect.w - 2, rect.y + 2, TRUE);
}
