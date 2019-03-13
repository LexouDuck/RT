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

void	ui_menu_file_open(void)
{
	debug_output("File->Open\n");
	g_rt.ui.current_prompt.textbox = texttype_text;
	g_rt.ui.current_prompt.text = ft_strdup("./");
	g_rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_OPEN;
	g_rt.ui.current_prompt.description =
		"Type in the file(s) to open.";
	g_rt.ui.current_prompt.rect = PROMPT;
	return ;
}

void	ui_menu_file_import(void)
{
	debug_output("File->Import\n");
	g_rt.ui.current_prompt.textbox = texttype_text;
	g_rt.ui.current_prompt.text = ft_strdup("./");
	g_rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_IMPORT;
	g_rt.ui.current_prompt.description =
		"Type in the file(s) to import to the scene.";
	g_rt.ui.current_prompt.rect = PROMPT;
	return ;
}

void	ui_menu_file_save(void)
{
	debug_output("File->Save\n");
	if (g_rt.filepath)
	{
		rt_file_save(g_rt.filepath);
	}
	else
	{
		g_rt.ui.current_prompt.textbox = texttype_text;
		g_rt.ui.current_prompt.text = ft_strdup("./");
		g_rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_SAVE;
		g_rt.ui.current_prompt.description =
			"Type in the destination filepath.";
		g_rt.ui.current_prompt.rect = PROMPT;
	}
	return ;
}

void	ui_menu_file_saveas(void)
{
	debug_output("File->SaveAs\n");
	g_rt.ui.current_prompt.textbox = texttype_text;
	g_rt.ui.current_prompt.text = ft_strdup("./");
	g_rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_SAVEAS;
	g_rt.ui.current_prompt.description =
		"Type in the destination filepath.";
	g_rt.ui.current_prompt.rect = PROMPT;
	return ;
}
