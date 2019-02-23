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
# include "rt_scene.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define UI_WIDTH_TILES	30
# define UI_WIDTH		TILE * UI_WIDTH_TILES

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

# define OBJECT_PROPERTY_H		4
# define OBJECT_PROPERTIES		5
# define OBJECT_PROPERTIES_H	OBJECT_PROPERTY_H * OBJECT_PROPERTIES

typedef struct	s_menu
{
	t_s8		item_amount;
	char const	*item_labels[MENU_MAX_ITEMS];
	SDL_Rect	item_hitbox[MENU_MAX_ITEMS];
	t_u32		item_hotkey[MENU_MAX_ITEMS];
//	void		(*items)(void)[MENU_MAX_ITEMS];
	t_s8		selection;
}				t_menu;

typedef enum	e_scrolling
{
	scrollclick_none = 0,
	scrollclick_button_up,
	scrollclick_button_down,
	scrollclick_bar_above,
	scrollclick_bar_below,
	scrollclick_bar
}				t_scrolling;

typedef struct	s_scrollbar
{
	t_scrolling	clicked;
	SDL_Rect	button_up;
	SDL_Rect	button_down;
	SDL_Rect	bar;
	t_s32		scroll;			// the current pixel y value
	t_s32		scroll_max;		// the amount of pixels to fit the entire list (with expanded objects and all)
	t_s32		scroll_view;	// the amount of pixels visible in the window, vertically
}				t_scrollbar;

typedef struct	s_menulist
{
	SDL_Rect	rect;
	t_bool		selected[OBJECT_MAX_AMOUNT];
	t_bool		expanded[OBJECT_MAX_AMOUNT];
	t_scrollbar	scrollbar;
}				t_menulist;

typedef struct	s_ui
{
	t_u8 const	*chr;
	t_u32		pal[PALETTE];
	SDL_Palette	*palette;
	SDL_Surface	*tileset;

	t_menu		menubar;
	t_menu		dropdowns[MENUBAR_ITEMS];
	t_menulist	objects;
}				t_ui;

/*
**	ui.c
*/
int				ui_init();
SDL_Palette*	ui_set_palette(SDL_Surface *surface, t_u32 const *palette);
SDL_Surface*	ui_set_tileset(t_u8 const *chr, size_t length);

/*
**	ui_render.c
*/
void	ui_render_objects();
void	ui_render_menubar();
void	ui_render_dropdown(t_menu *dropdown);
void	ui_render_caminfo(t_camera *camera);
void	ui_render_scrollbar(t_scrollbar *scrollbar);

/*
**	ui_mouse.c
*/
void	ui_mouse_menubar();
void	ui_mouse_dropdown(t_menu *dropdown);
void	ui_mouse_objectlist();
void	ui_mouse_scrollbar();

void	ui_scrollbar_setscroll(t_scrollbar *scrollbar, t_s32 scroll);

/*
**	ui_render_util.c
*/
void	ui_render_fill(t_u8 tile_index,
	SDL_Rect dest_region, t_bool transparent);
void	ui_render_icon(t_u8 icon_index,
	t_s32 x, t_s32 y, t_bool transparent);
void	ui_render_text(char const *str,
	t_s32 x, t_s32 y, t_bool transparent);
void	ui_render_rect(SDL_Rect rect, t_bool filled);

/*
**	ui_control_numberbox.c
**	ui_control_colorbox.c
**	ui_control_textbox.c
*/
void	ui_render_control_numberbox(int x, int y, cl_float value);

#endif
