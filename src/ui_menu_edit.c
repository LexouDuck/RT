/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "debug.h"

void		ui_menu_edit_undo()
{
	debug_output("Edit->Undo\n");
}

void		ui_menu_edit_redo()
{
	debug_output("Edit->Redo\n");
}

void		ui_menu_edit_cut()
{
	debug_output("Edit->Cut\n");
}

void		ui_menu_edit_copy()
{
	debug_output("Edit->Copy\n");
}

void		ui_menu_edit_paste()
{
	debug_output("Edit->Paste\n");
}
