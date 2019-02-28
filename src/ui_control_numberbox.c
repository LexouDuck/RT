/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_control_numberbox.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft_string.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

void	ui_leave_control_numberbox(t_textinput *textinput)
{
	cl_float	*value;

	if (textinput->value && rt.ui.current_textinput.value_changed)
	{
		value = (cl_float *)textinput->value;
		*value = textinput->input ? ft_str_to_f32(textinput->input) : 0;
		if (isnan(*value))
			*value = 0;
		rt.must_render = TRUE;
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

void	ui_keypress_control_numberbox(t_textinput *textinput, t_bool up)
{
	cl_float *value;

	value = (cl_float *)textinput->value;
	if (up)
		*value += 1.;
	else
		*value -= 1.0;
	rt.must_render = TRUE;
	ui_leave_control_numberbox(textinput);
			textinput->type = texttype_number_float;
			textinput->input = ft_f32_to_str(*value, 4);
			textinput->value = (void *)value;
			rt.ui.current_textinput.value_changed = FALSE;
			SDL_StartTextInput();
}

void	ui_mouse_control_numberbox(t_textinput *textinput, cl_float *value, int x, int y)
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
			*value += 0.500;
			rt.must_render = TRUE;
		}
		else if ((button.y += 2 * TILE) && SDL_PointInRect(&rt.input.mouse, &button))
		{
			*value -= 0.500;
			rt.must_render = TRUE;
		}
		else
		{
			textinput->type = texttype_number_float;
			textinput->input = ft_f32_to_str(*value, 4);
			textinput->value = (void *)value;
			rt.ui.current_textinput.value_changed = FALSE;
			SDL_StartTextInput();
		}
	}
}

void	ui_render_control_numberbox(int x, int y, cl_float *value)
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
