/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "../assets.h"
#include "debug.h"
#include "ui.h"

static void	ui_init_menubar()
{
	int i;

	rt.ui.menubar.selection = -1;
	rt.ui.menubar.item_amount = MENUBAR_ITEMS;
	rt.ui.menubar.item_labels[MENUBAR_ITEM_FILE] = MENUBAR_LABEL_FILE;
	rt.ui.menubar.item_labels[MENUBAR_ITEM_EDIT] = MENUBAR_LABEL_EDIT;
	rt.ui.menubar.item_labels[MENUBAR_ITEM_VIEW] = MENUBAR_LABEL_VIEW;
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
	dropdown->item_labels[DROPDOWN_FILE_OPEN]	= DROPDOWN_LABEL_FILE_OPEN;
	dropdown->item_labels[DROPDOWN_FILE_IMPORT]	= DROPDOWN_LABEL_FILE_IMPORT;
	dropdown->item_labels[DROPDOWN_FILE_SAVE]	= DROPDOWN_LABEL_FILE_SAVE;
	dropdown->item_labels[DROPDOWN_FILE_SAVEAS]	= DROPDOWN_LABEL_FILE_SAVEAS;
	dropdown->item_action[DROPDOWN_FILE_OPEN]	= ui_menu_file_open;
	dropdown->item_action[DROPDOWN_FILE_IMPORT]	= ui_menu_file_import;
	dropdown->item_action[DROPDOWN_FILE_SAVE]	= ui_menu_file_save;
	dropdown->item_action[DROPDOWN_FILE_SAVEAS]	= ui_menu_file_saveas;
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
	dropdown->item_labels[DROPDOWN_EDIT_UNDO]	= DROPDOWN_LABEL_EDIT_UNDO;
	dropdown->item_labels[DROPDOWN_EDIT_REDO]	= DROPDOWN_LABEL_EDIT_REDO;
	dropdown->item_labels[DROPDOWN_EDIT_CUT]	= DROPDOWN_LABEL_EDIT_CUT;
	dropdown->item_labels[DROPDOWN_EDIT_COPY]	= DROPDOWN_LABEL_EDIT_COPY;
	dropdown->item_labels[DROPDOWN_EDIT_PASTE]	= DROPDOWN_LABEL_EDIT_PASTE;
	dropdown->item_action[DROPDOWN_EDIT_UNDO]	= ui_menu_edit_undo;
	dropdown->item_action[DROPDOWN_EDIT_REDO]	= ui_menu_edit_redo;
	dropdown->item_action[DROPDOWN_EDIT_CUT]	= ui_menu_edit_cut;
	dropdown->item_action[DROPDOWN_EDIT_COPY]	= ui_menu_edit_copy;
	dropdown->item_action[DROPDOWN_EDIT_PASTE]	= ui_menu_edit_paste;
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
	dropdown->item_action[DROPDOWN_VIEW_ORTHOGONAL]	= ui_menu_view_orthogonal;
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

static void	ui_init_objectlist()
{
	rt.ui.objects.rect.x = 0;
	rt.ui.objects.rect.y = 4;
	rt.ui.objects.rect.w = UI_WIDTH_TILES - 2;
	rt.ui.objects.rect.h = rt.sdl.window_h - rt.ui.objects.rect.y;
	rt.ui.objects.scrollbar.clicked = scrollclick_none;
	rt.ui.objects.scrollbar.button_up = (SDL_Rect)
		{ UI_WIDTH - TILE * 2, TILE * MENUBAR_ITEMS_H, TILE * 2, TILE * 2 };
	rt.ui.objects.scrollbar.button_down = (SDL_Rect)
		{ UI_WIDTH - TILE * 2, rt.sdl.window_h - TILE * 2, TILE * 2, TILE * 2 };
	rt.ui.objects.scrollbar.bar = (SDL_Rect)
		{ UI_WIDTH - TILE * 2, TILE * (MENUBAR_ITEMS_H + 2), TILE * 2, rt.ui.objects.scrollbar.button_down.y - (TILE * (MENUBAR_ITEMS_H + 2)) };
	rt.ui.objects.scrollbar.scroll = 0;
	rt.ui.objects.scrollbar.scroll_max = 0;
	rt.ui.objects.scrollbar.scroll_view = (rt.sdl.window_h - MENUBAR_ITEMS_H);
}

int			ui_init()
{
	static const t_u32	palette[PALETTE] = {
		0x000000,
		0x0058F8,
		0x3CBCFC,
		0xFCFCFC
	};

#ifdef __APPLE__
	size_t		size = 0;
	rt.ui.chr = getsectiondata(&_mh_execute_header,
		"__DATA", "__inc_ui_chr", &size);
	if (size != CHR_SIZE)
		debug_output_value(
			"Invalid binary size: ", FT_Size_To_String(size), TRUE);
#else
	rt.ui.chr = _binary___inc_ui_chr_start;
#endif
	if (!(rt.ui.tileset = ui_set_tileset(rt.ui.chr, CHR_SIZE)))
		return (ERROR);
	if (!(ui_set_palette(rt.ui.tileset, palette)))
		return (ERROR);
	ft_memcpy(&rt.ui.pal, palette, PALETTE * sizeof(t_u32));
	ui_init_menubar();
	ui_init_dropdown_file();
	ui_init_dropdown_edit();
	ui_init_dropdown_view();
	ui_init_objectlist();
	SDL_StopTextInput();
	return (OK);
}
