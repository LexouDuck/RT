/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UI_H
# define __UI_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include "SDL.h"
# include "libft.h"

# include "../assets.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define UI_WIDTH	30 * TILE

# define MENU_MAX_ITEMS	8

# define MENUBAR_ITEMS_W	10
# define MENUBAR_ITEMS_H	3

# define MENUBAR_ITEM_FILE	0
# define MENUBAR_ITEM_EDIT	1
# define MENUBAR_ITEM_VIEW	2
# define MENUBAR_ITEMS		3

# define DROPDOWN_ITEMS_W		30
# define DROPDOWN_ITEMS_H		2

# define DROPDOWN_FILE_OPEN		0
# define DROPDOWN_FILE_IMPORT	1
# define DROPDOWN_FILE_SAVE		2
# define DROPDOWN_FILE_SAVEAS	3
# define DROPDOWN_ITEMS_FILE	4

# define DROPDOWN_EDIT_UNDO		0
# define DROPDOWN_EDIT_REDO		1
# define DROPDOWN_EDIT_CUT		2
# define DROPDOWN_EDIT_COPY		3
# define DROPDOWN_EDIT_PASTE	4
# define DROPDOWN_ITEMS_EDIT	5

# define DROPDOWN_VIEW_ORTHOGONAL	0
# define DROPDOWN_VIEW_DIFFUSE		1
# define DROPDOWN_VIEW_SPECULAR		2
# define DROPDOWN_VIEW_GLOBAL_I		3
# define DROPDOWN_ITEMS_VIEW		4

typedef struct	s_menu
{
	t_s8		item_amount;
	char const	*item_labels[MENU_MAX_ITEMS];
	SDL_Rect	item_hitbox[MENU_MAX_ITEMS];
	t_u32		item_hotkey[MENU_MAX_ITEMS];
//	void		(*items)(void)[MENU_MAX_ITEMS];
	t_s8		selection;
}				t_menu;

typedef struct	s_ui
{
	t_u8 const	*chr;
	t_u32		pal[PALETTE];
	SDL_Palette	*palette;
	SDL_Surface	*tileset;

	t_menu		menubar;
	t_menu		dropdowns[MENUBAR_ITEMS];
}				t_ui;

/*
**	ui.c
*/
int				ui_init();
SDL_Palette*	ui_set_palette(SDL_Surface *surface, t_u32 const *palette);
SDL_Surface*	ui_set_tileset(t_u8 const *chr, size_t length);

/*
**	render_ui.c
*/
void	render_ui_menubar();
void	render_ui_dropdown(t_menu *dropdown);
void	render_ui_text(
	char const *str,
	t_s32 x,
	t_s32 y,
	t_bool transparent);
void	render_ui_rect(SDL_Rect rect, t_bool filled);

#endif