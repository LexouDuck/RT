/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

void		ui_menu_file_open()
{
	debug_output("File->Open\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.name = "Open file prompt";
	rt.ui.current_prompt.description = "Type in the file(s) to open.";
}

void		ui_menu_file_import()
{
	debug_output("File->Import\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.name = "Import file prompt";
	rt.ui.current_prompt.description = "Type in the file(s) to import to the scene.";
}

void		ui_menu_file_save()
{
	debug_output("File->Save\n");
	if (rt.filepath)
	{
		//rt_file_save(rt.filepath);
	}
	else
	{
		rt.ui.current_prompt.textbox = texttype_text;
		rt.ui.current_prompt.name = "Save file prompt";
		rt.ui.current_prompt.description = "Type in the destination filepath.";
	}
}

void		ui_menu_file_saveas()
{
	debug_output("File->SaveAs\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.name = "Save file prompt";
	rt.ui.current_prompt.description = "Type in the destination filepath.";
}
