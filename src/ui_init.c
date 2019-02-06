/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"
#include "../assets.h"

static void	ui_init_menubar()
{
	int i;

	rt.ui.menubar.selection = -1;
	rt.ui.menubar.item_amount = MENUBAR_ITEMS;
	rt.ui.menubar.item_labels[MENUBAR_ITEM_FILE] = "File";
	rt.ui.menubar.item_labels[MENUBAR_ITEM_EDIT] = "Edit";
	rt.ui.menubar.item_labels[MENUBAR_ITEM_VIEW] = "View";
	i = 0;
	while (i < MENUBAR_ITEMS)
	{
		rt.ui.menubar.item_hitbox[i].x = MENUBAR_ITEMS_W * i;
		rt.ui.menubar.item_hitbox[i].y = 0;
		rt.ui.menubar.item_hitbox[i].w = MENUBAR_ITEMS_W;
		rt.ui.menubar.item_hitbox[i].h = MENUBAR_ITEMS_H;
		++i;
	}
}

static void	ui_init_dropdown_file()
{
	t_menu* dropdown;
	int i;

	dropdown = &rt.ui.dropdowns[MENUBAR_ITEM_FILE];
	dropdown->selection = -1;
	dropdown->item_amount = DROPDOWN_ITEMS_FILE;
	dropdown->item_labels[DROPDOWN_FILE_OPEN]	= "Open file...";
	dropdown->item_labels[DROPDOWN_FILE_IMPORT]	= "Import file...";
	dropdown->item_labels[DROPDOWN_FILE_SAVE]	= "Save";
	dropdown->item_labels[DROPDOWN_FILE_SAVEAS]	= "Save as...";
	i = 0;
	while (i < DROPDOWN_ITEMS_FILE)
	{
		dropdown->item_hitbox[i].x = 0;
		dropdown->item_hitbox[i].y = 3 + DROPDOWN_ITEMS_H * i;
		dropdown->item_hitbox[i].w = DROPDOWN_ITEMS_W;
		dropdown->item_hitbox[i].h = DROPDOWN_ITEMS_H;
		++i;
	}
}

static void	ui_init_dropdown_edit()
{
	t_menu* dropdown;
	int i;

	dropdown = &rt.ui.dropdowns[MENUBAR_ITEM_EDIT];
	dropdown->selection = -1;
	dropdown->item_amount = DROPDOWN_ITEMS_EDIT;
	dropdown->item_labels[DROPDOWN_EDIT_UNDO]	= "Undo";
	dropdown->item_labels[DROPDOWN_EDIT_REDO]	= "Redo";
	dropdown->item_labels[DROPDOWN_EDIT_CUT]	= "Cut";
	dropdown->item_labels[DROPDOWN_EDIT_COPY]	= "Copy";
	dropdown->item_labels[DROPDOWN_EDIT_PASTE]	= "Paste";
	i = 0;
	while (i < DROPDOWN_ITEMS_EDIT)
	{
		dropdown->item_hitbox[i].x = 0;
		dropdown->item_hitbox[i].y = 3 + DROPDOWN_ITEMS_H * i;
		dropdown->item_hitbox[i].w = DROPDOWN_ITEMS_W;
		dropdown->item_hitbox[i].h = DROPDOWN_ITEMS_H;
		++i;
	}
}

static void	ui_init_dropdown_view()
{
	t_menu* dropdown;
	int i;

	dropdown = &rt.ui.dropdowns[MENUBAR_ITEM_VIEW];
	dropdown->selection = -1;
	dropdown->item_amount = DROPDOWN_ITEMS_VIEW;
	dropdown->item_labels[DROPDOWN_VIEW_ORTHOGONAL]	= "Orthogonal projection";
	dropdown->item_labels[DROPDOWN_VIEW_DIFFUSE]	= "Diffuse lighting";
	dropdown->item_labels[DROPDOWN_VIEW_SPECULAR]	= "Specular lighting";
	dropdown->item_labels[DROPDOWN_VIEW_GLOBAL_I]	= "Global illumination";
	i = 0;
	while (i < DROPDOWN_ITEMS_VIEW)
	{
		dropdown->item_hitbox[i].x = 0;
		dropdown->item_hitbox[i].y = 3 + DROPDOWN_ITEMS_H * i;
		dropdown->item_hitbox[i].w = DROPDOWN_ITEMS_W;
		dropdown->item_hitbox[i].h = DROPDOWN_ITEMS_H;
		++i;
	}
}

int			ui_init()
{
	static const t_u32 palette[PALETTE] = {
		0x000000,
		0x0058F8,
		0x3CBCFC,
		0xFCFCFC
	};

#ifdef __APPLE__
	rt.ui.chr = _section$__DATA____inc_ui_chr;
#else
	rt.ui.chr = _binary___inc_ui_chr_start;
#endif
	if (!(rt.ui.tileset = ui_set_tileset(rt.ui.chr, CHR_SIZE)))
		return (ERROR);
	if (!(ui_set_palette(rt.ui.tileset, palette)))
		return (ERROR);
	ui_init_menubar();
	ui_init_dropdown_file();
	ui_init_dropdown_edit();
	ui_init_dropdown_view();
	return (OK);
}
