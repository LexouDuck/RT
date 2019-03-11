/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:42:51 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

void		ui_menu_file_open(void)
{
	debug_output("File->Open\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.text = ft_strdup("./");
	rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_OPEN;
	rt.ui.current_prompt.description = "Type in the file(s) to open.";
	rt.ui.current_prompt.rect = PROMPT;
}

void		ui_menu_file_import(void)
{
	debug_output("File->Import\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.text = ft_strdup("./");
	rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_IMPORT;
	rt.ui.current_prompt.description = "Type in the file(s) to import to the scene.";
	rt.ui.current_prompt.rect = PROMPT;
}

void		ui_menu_file_saveas(void)
{
	debug_output("File->SaveAs\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.text = ft_strdup("./");
	rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_SAVEAS;
	rt.ui.current_prompt.description = "Type in the destination filepath.";
	rt.ui.current_prompt.rect = PROMPT;
}

void		ui_menu_file_generate(void)
{
	debug_output("File->Generate\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.text = ft_strdup("./");
	rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_RANDOM;
	rt.ui.current_prompt.description = "Type in the destination filepath.";
	rt.ui.current_prompt.rect = PROMPT;
}

void		ui_menu_file_exportbmp(void)
{
	debug_output("File->ExportBMP\n");
	rt.ui.current_prompt.textbox = texttype_text;
	rt.ui.current_prompt.text = ft_strdup("./");
	rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_SAVEBMP;
	rt.ui.current_prompt.description = "Type in the destination filepath.";
	rt.ui.current_prompt.rect = PROMPT;
}
