/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

#include "../rt.h"
#include "event.h"

static t_bool	event_check_keydown_windowevents(SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		if (rt.sdl.fullscreen)
			event_window_fullscreen(FALSE);
		else
			rt.sdl.loop = FALSE;
		return (TRUE);
	}
	if (event->key.keysym.sym == SDLK_RETURN && (rt.input.keys & KEY_ALT))
	{
		if (!rt.sdl.fullscreen)
			event_window_fullscreen(TRUE);
		return (TRUE);
	}
	if (rt.ui.current_textinput.type == texttype_none)
	{
		if (event->key.keysym.sym == SDLK_SPACE)
			rt.must_render = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	event_check_keydown_special_numberbox(SDL_Event *event)
{
	float	*tmp;

	if (event->key.keysym.sym == SDLK_TAB &&
		rt.ui.current_textinput.type == texttype_number_float)
	{
		tmp = rt.ui.current_textinput.value;
		tmp += (rt.input.keys & KEY_SHIFT_L) ? -1 : 1;
		rt.ui.current_textinput.value = tmp;
		rt.ui.current_textinput.input = ft_f32_to_str(*tmp, 4);
		return (TRUE);
	}
	if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN)
	{
		if (rt.ui.current_textinput.type == texttype_number_int)
			ui_keypress_control_textbox(&rt.ui.current_textinput);
		else if (rt.ui.current_textinput.type == texttype_number_int)
			ui_keypress_control_numberbox_int(&rt.ui.current_textinput,
				event->key.keysym.sym == SDLK_UP);
		else if (rt.ui.current_textinput.type == texttype_number_float)
			ui_keypress_control_numberbox_float(&rt.ui.current_textinput,
				event->key.keysym.sym == SDLK_UP);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	event_check_keydown_special_textinput(SDL_Event *event)
{
	size_t length;

	length = ft_strlen(rt.ui.current_textinput.input);
	if (event->key.keysym.sym == SDLK_RETURN ||
		event->key.keysym.sym == SDLK_KP_ENTER)
	{
		if (rt.ui.current_textinput.type == texttype_text)
			ui_leave_control_textbox(&rt.ui.current_textinput);
		else if (rt.ui.current_textinput.type == texttype_number_int)
			ui_leave_control_numberbox_int(&rt.ui.current_textinput);
		else if (rt.ui.current_textinput.type == texttype_number_float)
			ui_leave_control_numberbox_float(&rt.ui.current_textinput);
		return (TRUE);
	}
	else if (event->key.keysym.sym == SDLK_BACKSPACE && length > 0)
		rt.ui.current_textinput.input[length - 1] = '\0';
	else if ((rt.input.keys & KEY_CTRL) && event->key.keysym.sym == SDLK_c)
		SDL_SetClipboardText(rt.ui.current_textinput.input);
	else if ((rt.input.keys & KEY_CTRL) && event->key.keysym.sym == SDLK_v)
	{
		rt.ui.current_textinput.input = SDL_GetClipboardText();
		rt.ui.current_textinput.value_changed = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void			event_check_keydown(SDL_Event *event)
{
	if (event_check_keydown_windowevents(event))
		return ;
	if (rt.ui.current_textinput.type)
	{
		if (event_check_keydown_special_numberbox(event))
			return ;
		if (event_check_keydown_special_textinput(event))
			return ;
	}
	if (event->key.keysym.sym == SDLK_LALT)
		rt.input.keys |= KEY_ALT_L;
	else if (event->key.keysym.sym == SDLK_RALT)
		rt.input.keys |= KEY_ALT_R;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		rt.input.keys |= KEY_CTRL_L;
	else if (event->key.keysym.sym == SDLK_RCTRL)
		rt.input.keys |= KEY_CTRL_R;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		rt.input.keys |= KEY_SHIFT_L;
	else if (event->key.keysym.sym == SDLK_RSHIFT)
		rt.input.keys |= KEY_SHIFT_R;
}

void			event_check_keyup(SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_LALT)
		rt.input.keys &= ~KEY_ALT_L;
	else if (event->key.keysym.sym == SDLK_RALT)
		rt.input.keys &= ~KEY_ALT_R;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		rt.input.keys &= ~KEY_CTRL_L;
	else if (event->key.keysym.sym == SDLK_RCTRL)
		rt.input.keys &= ~KEY_CTRL_R;
	else if (event->key.keysym.sym == SDLK_LSHIFT)
		rt.input.keys &= ~KEY_SHIFT_L;
	else if (event->key.keysym.sym == SDLK_RSHIFT)
		rt.input.keys &= ~KEY_SHIFT_R;
}
