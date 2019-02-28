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

void	ui_leave_prompt(void)
{
	if (rt.ui.current_textinput.type)
		ui_leave_control_textbox(&rt.ui.current_textinput);
	rt.ui.current_prompt.textbox = texttype_none;
	rt.ui.current_prompt.name = NULL;
	rt.ui.current_prompt.description = NULL;
	rt.ui.menubar.selection = -1;
}

void	ui_mouse_prompt(void)
{
	static SDL_Rect	button_ok = PROMPT_BUTTON_OK;
	static SDL_Rect	button_cancel = PROMPT_BUTTON_CANCEL;

	if (SDL_PointInRect(&rt.input.mouse_tile, &rt.ui.current_prompt.rect))
	{
		if (SDL_PointInRect(&rt.input.mouse_tile, &button_cancel))
			ui_leave_prompt();
		else if (SDL_PointInRect(&rt.input.mouse_tile, &button_ok))
		{
			if (rt.ui.current_prompt.name == NULL)
				debug_output_error("Invalid dropdown label name upon prompt apply.", FALSE);
			else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_OPEN))
				rt_file_open(rt.ui.current_prompt.text);
			else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_IMPORT))
				rt_file_import(rt.ui.current_prompt.text);
			else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_SAVE))
				rt_file_save(rt.ui.current_prompt.text);
			else if (ft_strequ(rt.ui.current_prompt.name, DROPDOWN_LABEL_FILE_SAVEAS))
				rt_file_save(rt.ui.current_prompt.text);
			ui_leave_prompt();
		}
		else
			ui_mouse_control_textbox(&rt.ui.current_textinput, &rt.ui.current_prompt.text, 2, 8);
	}
	else
		ui_leave_prompt();
}
