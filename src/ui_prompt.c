/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:57:11 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"

#include "../rt.h"
#include "debug.h"
#include "rt_random.h"

static void	ui_cancel_prompt(void)
{
	if (rt.ui.current_textinput.type)
		ui_leave_control_textbox(&rt.ui.current_textinput);
	rt.ui.current_prompt.textbox = texttype_none;
	rt.ui.current_prompt.name = NULL;
	rt.ui.current_prompt.description = NULL;
	rt.ui.menubar.selection = -1;
	rt.ui.objects.scrollbar.scroll = 0;
	rt.ui.objects.scrollbar.scroll_max = 0;
	ft_memclr(&rt.ui.objects.selected, sizeof(t_bool) * OBJECT_MAX_AMOUNT);
	ft_memclr(&rt.ui.objects.expanded, sizeof(t_bool) * OBJECT_MAX_AMOUNT);
	return ;
}

static void	ui_accept_prompt(void)
{
	if (rt.ui.current_prompt.name == NULL)
		debug_output_error(
			"Invalid dropdown label name upon prompt apply.", FALSE);
	else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_OPEN))
		rt_file_open(rt.ui.current_prompt.text);
	else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_IMPORT))
		rt_file_import(rt.ui.current_prompt.text);
	else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_SAVE))
		rt_file_save(rt.ui.current_prompt.text);
	else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_SAVEAS))
		rt_file_save(rt.ui.current_prompt.text);
	else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_RANDOM))
		rt_auto_build_scene(rt.ui.current_prompt.text);
	else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_SAVEBMP))
		if (SDL_SaveBMP(rt.canvas, rt.ui.current_prompt.text))
			debug_output_error(
				"Could not save BMP image of the render: ", TRUE);
	ui_cancel_prompt();
	rt.must_render = TRUE;
	return ;
}

void		ui_mouse_prompt(void)
{
	static SDL_Rect	button_ok = PROMPT_BUTTON_OK;
	static SDL_Rect	button_cancel = PROMPT_BUTTON_CANCEL;

	if (SDL_PointInRect(&rt.input.mouse_tile, &rt.ui.current_prompt.rect))
	{
		if (SDL_PointInRect(&rt.input.mouse_tile, &button_cancel))
			ui_cancel_prompt();
		else if (SDL_PointInRect(&rt.input.mouse_tile, &button_ok))
			ui_accept_prompt();
		else
			ui_mouse_control_textbox(&rt.ui.current_textinput,
				&rt.ui.current_prompt.text, 2, 8);
	}
	else
		ui_cancel_prompt();
	return ;
}
