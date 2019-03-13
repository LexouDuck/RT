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

# define UI_WIDTH_TILES		30
# define UI_WIDTH			TILE * UI_WIDTH_TILES

# define MENU_MAX_ITEMS	8
# define MENUBAR_ITEMS_W	10
# define MENUBAR_ITEMS_H	3

# define MENUBAR_ITEM_FILE	0
# define MENUBAR_ITEM_EDIT	1
# define MENUBAR_ITEMS		2
# define MENUBAR_LABEL_FILE	"File"
# define MENUBAR_LABEL_EDIT	"Edit"

# define DROPDOWN_ITEMS_W		30
# define DROPDOWN_ITEMS_H		2

# define DROPDOWN_FILE_OPEN			0
# define DROPDOWN_FILE_IMPORT		1
# define DROPDOWN_FILE_SAVE			2
# define DROPDOWN_FILE_SAVEAS		3
# define DROPDOWN_FILE_RANDOM		4
# define DROPDOWN_FILE_SAVEBMP		5
# define DROPDOWN_ITEMS_FILE		6
# define DROPDOWN_LABEL_FILE_OPEN		"Open file..."
# define DROPDOWN_LABEL_FILE_IMPORT		"Import file..."
# define DROPDOWN_LABEL_FILE_SAVE		"Save"
# define DROPDOWN_LABEL_FILE_SAVEAS		"Save as..."
# define DROPDOWN_LABEL_FILE_RANDOM		"Generate file..."
# define DROPDOWN_LABEL_FILE_SAVEBMP	"Export BMP image..."

# define DROPDOWN_EDIT_UNDO		0
# define DROPDOWN_EDIT_REDO		1
# define DROPDOWN_EDIT_CUT		2
# define DROPDOWN_EDIT_COPY		3
# define DROPDOWN_EDIT_PASTE	4
# define DROPDOWN_ITEMS_EDIT	5
# define DROPDOWN_LABEL_EDIT_UNDO	"Undo"
# define DROPDOWN_LABEL_EDIT_REDO	"Redo"
# define DROPDOWN_LABEL_EDIT_CUT	"Cut"
# define DROPDOWN_LABEL_EDIT_COPY	"Copy"
# define DROPDOWN_LABEL_EDIT_PASTE	"Paste"

# define OBJECT_PROPERTY_H		4
# define OBJECT_PROPERTIES		12
# define OBJECT_PROPERTIES_H	OBJECT_PROPERTY_H * (OBJECT_PROPERTIES + 3)

typedef struct	s_menu
{
	t_s8		item_amount;
	char const	*item_labels[MENU_MAX_ITEMS];
	SDL_Rect	item_hitbox[MENU_MAX_ITEMS];
	t_u32		item_hotkey[MENU_MAX_ITEMS];
	void		(*item_action[MENU_MAX_ITEMS])(void);
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

/*
**	The struct which holds all current scrollbar info
**	- scroll		the current pixel y value
**	- scroll_max	the amount of vertical pixels for the entire list
**	- scroll_view	the amount of vertical pixels visible in the window
*/
typedef struct	s_scrollbar
{
	t_scrolling	clicked;
	SDL_Rect	button_up;
	SDL_Rect	button_down;
	SDL_Rect	bar;
	t_s32		scroll;
	t_s32		scroll_max;
	t_s32		scroll_view;
}				t_scrollbar;

typedef struct	s_menulist
{
	SDL_Rect	rect;
	t_bool		selected[OBJECT_MAX_AMOUNT];
	t_bool		expanded[OBJECT_MAX_AMOUNT];
	t_scrollbar	scrollbar;
}				t_menulist;

typedef enum	e_texttype
{
	texttype_none = 0,
	texttype_number_int,
	texttype_number_hex,
	texttype_number_float,
	texttype_text,
}				t_texttype;

/*
**	This struct holds current text input selection info
**	if 'type' is 0 (texttype_none), nothing is selected
**	otherwise, the 'type' will inform how to convert the
**	contents of 'input' to write it into 'value'
**	Fields:
**	- type			The type of keyboard input box selected
**	- input			The string of text that the user has entered
**	- value			A pointer to the value in memory which needs to be changed
**	- value_changed	Whether or not text has been input by the user
*/
typedef struct	s_textinput
{
	t_texttype	type;
	char		*input;
	void		*value;
	t_bool		value_changed;
}				t_textinput;

/*
**	This struct holds the current UI pop-up dialog prompt
**	if 'textbox' is 0 (texttype_none), then there currently is no prompt open
*/
typedef struct	s_prompt
{
	char		*text;
	t_texttype	textbox;
	char const	*name;
	char const	*description;
	SDL_Rect	rect;
}				t_prompt;

# define PROMPT					(SDL_Rect){ 0, 4, UI_WIDTH_TILES, 12 }
# define PROMPT_BUTTON_OK		(SDL_Rect){ 5, 12, 8, 3 }
# define PROMPT_BUTTON_CANCEL	(SDL_Rect){ 17,12, 8, 3 }

/*
**	This struct holds all info pertaining to the UI sidebar
*/
typedef struct	s_ui
{
	t_u8 const	*chr;
	t_u32		pal[PALETTE];
	SDL_Palette	*palette;
	SDL_Surface	*tileset;

	t_menu		menubar;
	t_menu		dropdowns[MENUBAR_ITEMS];
	t_menulist	objects;
	t_textinput	current_textinput;
	t_prompt	current_prompt;
}				t_ui;

/*
**	ui.c
*/
int				ui_init();
int				ui_init_assets();
SDL_Palette		*ui_set_palette(SDL_Surface *surface, t_u32 const *palette);
SDL_Surface		*ui_set_tileset(t_u8 const *chr, size_t length);

/*
**	ui_menu_file.c
*/
void			ui_menu_file_open(void);
void			ui_menu_file_import(void);
void			ui_menu_file_save(void);
void			ui_menu_file_saveas(void);
void			ui_menu_file_generate(void);
void			ui_menu_file_exportbmp(void);

/*
**	ui_menu_edit.c
*/
void			ui_menu_edit_undo(void);
void			ui_menu_edit_redo(void);
void			ui_menu_edit_cut(void);
void			ui_menu_edit_copy(void);
void			ui_menu_edit_paste(void);

/*
**	ui_render.c
*/
void			ui_render_menubar(void);
void			ui_render_dropdown(t_menu *dropdown);
void			ui_render_objectlist(void);
void			ui_render_scrollbar(t_scrollbar *scrollbar);
void			ui_render_prompt(void);
void			ui_render_caminfo(t_camera *camera);
void			ui_render_loading_bar(void);

/*
**	ui_mouse.c
**	ui_mouse_objectlist.c
*/
void			ui_mouse_menu();
void			ui_mouse_menubar();
void			ui_mouse_dropdown(t_menu *dropdown);
void			ui_mouse_objectlist(void);
void			ui_mouse_scrollbar(void);
void			ui_mouse_prompt(void);

void			ui_scrollbar_setscroll(t_scrollbar *scrollbar, t_s32 scroll);
t_bool			ui_mouse_objectlist_expandedproperties_primitive(
				t_primitive *primitive, t_s32 y);
t_bool			ui_mouse_objectlist_expandedproperties_material(
				t_material *material, t_s32 y);
t_bool			ui_mouse_objectlist_expandedproperties_pattern(
				t_pattern *pattern, t_s32 y);
t_bool			ui_mouse_objectlist_expandedproperties_projection(
				t_projection *projection, t_s32 y);
t_bool			ui_mouse_objectlist_expandedproperties_bump(
				t_bump *bump_type, t_s32 y);

/*
**	ui_render_util.c
*/
void			ui_render_fill(t_u8 tile_index,
				SDL_Rect dest_region, t_bool transparent);
void			ui_render_icon(t_u8 icon_index,
				t_s32 x, t_s32 y, t_bool transparent);
void			ui_render_text(char const *str,
				t_s32 x, t_s32 y, t_bool transparent);
void			ui_render_rect(SDL_Rect rect, t_bool filled);

/*
**	ui_control_numberbox_int.c
*/
void			ui_leave_control_numberbox_int(t_textinput *textinput);
t_bool			ui_mouse_control_numberbox_int(t_textinput *textinput,
				cl_uint *value, int x, int y);
void			ui_render_control_numberbox_int(
				int x, int y, cl_uint *value);
void			ui_keypress_control_numberbox_int(t_textinput *textinput,
				t_bool up);
/*
**	ui_control_numberbox_float.c
*/
void			ui_leave_control_numberbox_float(t_textinput *textinput);
t_bool			ui_mouse_control_numberbox_float(t_textinput *textinput,
				cl_float *value, int x, int y);
void			ui_render_control_numberbox_float(
				int x, int y, cl_float *value);
void			ui_keypress_control_numberbox_float(t_textinput *textinput,
				t_bool up);

/*
**	ui_control_textbox.c
*/
void			ui_leave_control_textbox(t_textinput *textinput);
t_bool			ui_mouse_control_textbox(t_textinput *textinput,
				char **value, int x, int y);
void			ui_render_control_textbox(
				int x, int y, char *value);
void			ui_keypress_control_textbox(t_textinput *textinput);

#endif
