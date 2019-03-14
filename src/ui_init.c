/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 16:05:34 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "ui.h"

static void	ui_init_menubar(void)
{
	int i;

	g_rt.ui.menubar.selection = -1;
	g_rt.ui.menubar.item_amount = MENUBAR_ITEMS;
	g_rt.ui.menubar.item_labels[MENUBAR_ITEM_FILE] = MENUBAR_LABEL_FILE;
	g_rt.ui.menubar.item_labels[MENUBAR_ITEM_EDIT] = MENUBAR_LABEL_EDIT;
	i = 0;
	while (i < MENUBAR_ITEMS)
	{
		g_rt.ui.menubar.item_hitbox[i].x = MENUBAR_ITEMS_W * i;
		g_rt.ui.menubar.item_hitbox[i].y = 0;
		g_rt.ui.menubar.item_hitbox[i].w = MENUBAR_ITEMS_W;
		g_rt.ui.menubar.item_hitbox[i].h = MENUBAR_ITEMS_H;
		++i;
	}
}

static void	ui_init_dropdown_file(t_menu *dropdown)
{
	int		i;

	dropdown->selection = -1;
	dropdown->item_amount = DROPDOWN_ITEMS_FILE;
	dropdown->item_labels[DROPDOWN_FILE_OPEN] = DROPDOWN_LABEL_FILE_OPEN;
	dropdown->item_labels[DROPDOWN_FILE_IMPORT] = DROPDOWN_LABEL_FILE_IMPORT;
	dropdown->item_labels[DROPDOWN_FILE_SAVE] = DROPDOWN_LABEL_FILE_SAVE;
	dropdown->item_labels[DROPDOWN_FILE_SAVEAS] = DROPDOWN_LABEL_FILE_SAVEAS;
	dropdown->item_labels[DROPDOWN_FILE_RANDOM] = DROPDOWN_LABEL_FILE_RANDOM;
	dropdown->item_labels[DROPDOWN_FILE_SAVEBMP] = DROPDOWN_LABEL_FILE_SAVEBMP;
	dropdown->item_action[DROPDOWN_FILE_OPEN] = ui_menu_file_open;
	dropdown->item_action[DROPDOWN_FILE_IMPORT] = ui_menu_file_import;
	dropdown->item_action[DROPDOWN_FILE_SAVE] = ui_menu_file_save;
	dropdown->item_action[DROPDOWN_FILE_SAVEAS] = ui_menu_file_saveas;
	dropdown->item_action[DROPDOWN_FILE_RANDOM] = ui_menu_file_generate;
	dropdown->item_action[DROPDOWN_FILE_SAVEBMP] = ui_menu_file_exportbmp;
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

static void	ui_init_dropdown_edit(t_menu *dropdown)
{
	int		i;

	dropdown->selection = -1;
	dropdown->item_amount = DROPDOWN_ITEMS_EDIT;
	dropdown->item_labels[DROPDOWN_EDIT_UNDO] = DROPDOWN_LABEL_EDIT_UNDO;
	dropdown->item_labels[DROPDOWN_EDIT_REDO] = DROPDOWN_LABEL_EDIT_REDO;
	dropdown->item_labels[DROPDOWN_EDIT_CUT] = DROPDOWN_LABEL_EDIT_CUT;
	dropdown->item_labels[DROPDOWN_EDIT_COPY] = DROPDOWN_LABEL_EDIT_COPY;
	dropdown->item_labels[DROPDOWN_EDIT_PASTE] = DROPDOWN_LABEL_EDIT_PASTE;
	dropdown->item_action[DROPDOWN_EDIT_UNDO] = ui_menu_edit_undo;
	dropdown->item_action[DROPDOWN_EDIT_REDO] = ui_menu_edit_redo;
	dropdown->item_action[DROPDOWN_EDIT_CUT] = ui_menu_edit_cut;
	dropdown->item_action[DROPDOWN_EDIT_COPY] = ui_menu_edit_copy;
	dropdown->item_action[DROPDOWN_EDIT_PASTE] = ui_menu_edit_paste;
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

static void	ui_init_objectlist(void)
{
	g_rt.ui.objects.rect.x = 0;
	g_rt.ui.objects.rect.y = 22;
	g_rt.ui.objects.rect.w = UI_WIDTH_TILES - 2;
	g_rt.ui.objects.rect.h = g_rt.sdl.window_h - g_rt.ui.objects.rect.y;
	g_rt.ui.objects.scrollbar.clicked = scrollclick_none;
	g_rt.ui.objects.scrollbar.button_up = (SDL_Rect)
		{ UI_WIDTH - TILE * 2, TILE * g_rt.ui.objects.rect.y,
			TILE * 2, TILE * 2 };
	g_rt.ui.objects.scrollbar.button_down = (SDL_Rect)
		{ UI_WIDTH - TILE * 2, g_rt.sdl.window_h - TILE * 2,
			TILE * 2, TILE * 2 };
	g_rt.ui.objects.scrollbar.bar = (SDL_Rect)
		{ UI_WIDTH - TILE * 2, TILE * (g_rt.ui.objects.rect.y + 2),
			TILE * 2, g_rt.ui.objects.scrollbar.button_down.y -
			(TILE * (g_rt.ui.objects.rect.y + 2)) };
	g_rt.ui.objects.scrollbar.scroll = 0;
	g_rt.ui.objects.scrollbar.scroll_max = 0;
	g_rt.ui.objects.scrollbar.scroll_view =
		(g_rt.sdl.window_h - g_rt.ui.objects.rect.y);
}

int			ui_init(void)
{
	static const t_u32	palette[PALETTE] = {
		0x000000, 0x0058F8, 0x3CBCFC, 0xFCFCFC };

	ui_init_assets();
	if (!(g_rt.ui.tileset = ui_set_tileset(g_rt.ui.chr, CHR_SIZE)))
		return (ERROR);
	if (!(ui_set_palette(g_rt.ui.tileset, palette)))
		return (ERROR);
	ft_memcpy(&g_rt.ui.pal, palette, PALETTE * sizeof(t_u32));
	ui_init_menubar();
	ui_init_dropdown_file(&g_rt.ui.dropdowns[MENUBAR_ITEM_FILE]);
	ui_init_dropdown_edit(&g_rt.ui.dropdowns[MENUBAR_ITEM_EDIT]);
	ui_init_objectlist();
	SDL_StopTextInput();
	return (OK);
}
