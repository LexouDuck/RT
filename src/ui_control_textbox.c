/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_control_textbox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:04:46 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft_string.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"

void	ui_leave_control_textbox(t_textinput *textinput)
{
	char	**value;

	if (textinput->value && g_rt.ui.current_textinput.value_changed)
	{
		value = (char **)textinput->value;
		if (*value)
			free(*value);
		*value = ft_strdup(textinput->input);
		g_rt.must_render = TRUE;
	}
	if (textinput->input)
	{
		free(textinput->input);
		textinput->input = NULL;
	}
	if (textinput->type)
	{
		textinput->type = texttype_none;
		SDL_StopTextInput();
	}
	return ;
}

t_bool	ui_mouse_control_textbox(t_textinput *textinput,
	char **value, int x, int y)
{
	static SDL_Rect	rect = { 0, 0, 26 * TILE, 3 * TILE };

	rect.x = x * TILE;
	rect.y = y * TILE;
	if (SDL_PointInRect(&g_rt.input.mouse, &rect))
	{
		textinput->type = texttype_text;
		textinput->input = ft_strdup(*value);
		textinput->value = (void *)value;
		g_rt.ui.current_textinput.value_changed = FALSE;
		SDL_StartTextInput();
		return (TRUE);
	}
	return (FALSE);
}

void	ui_render_control_textbox(int x, int y, char *value)
{
	static const size_t	str_max_length = 1024;
	static SDL_Rect		rect = { 0, 0, 26, 3 };

	rect.x = x;
	rect.y = y;
	ui_render_rect(rect, (value == g_rt.ui.current_textinput.value));
	if (value == g_rt.ui.current_textinput.value)
	{
		ui_render_text(g_rt.ui.current_textinput.input,
			rect.x + 1, rect.y + 1, FALSE);
	}
	else if (value)
	{
		if (ft_strlen(value) > str_max_length)
			value[str_max_length] = '\0';
		ui_render_text(value, rect.x + 1, rect.y + 1, FALSE);
	}
	return ;
}

void	ui_keypress_control_textbox(t_textinput *textinput)
{
	if (!textinput)
		return ;
	return ;
}
