/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_file_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:42:51 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

void	ui_menu_file_generate(void)
{
	debug_output("File->Generate\n");
	g_rt.ui.current_prompt.textbox = texttype_text;
	g_rt.ui.current_prompt.text = ft_strdup("./");
	g_rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_RANDOM;
	g_rt.ui.current_prompt.description =
		"Type in the destination filepath.";
	g_rt.ui.current_prompt.rect = PROMPT;
	return ;
}

void	ui_menu_file_exportbmp(void)
{
	debug_output("File->ExportBMP\n");
	g_rt.ui.current_prompt.textbox = texttype_text;
	g_rt.ui.current_prompt.text = ft_strdup("./");
	g_rt.ui.current_prompt.name = DROPDOWN_LABEL_FILE_SAVEBMP;
	g_rt.ui.current_prompt.description =
		"Type in the destination filepath.";
	g_rt.ui.current_prompt.rect = PROMPT;
	return ;
}
