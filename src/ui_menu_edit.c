/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:42:01 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

void		ui_menu_edit_undo(void)
{
	debug_output("Edit->Undo\n");
}

void		ui_menu_edit_redo(void)
{
	debug_output("Edit->Redo\n");
}

void		ui_menu_edit_cut(void)
{
	debug_output("Edit->Cut\n");
}

void		ui_menu_edit_copy(void)
{
	debug_output("Edit->Copy\n");
}

void		ui_menu_edit_paste(void)
{
	debug_output("Edit->Paste\n");
}
