/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
#define CONFIG_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define CONFIG_FILE		"config.ini"

#define CONFIG_AMOUNT	4

/*
**	This struct is meant to hold all persistent program data (in strings)
*/
typedef	struct	s_config
{
	char const*	names[CONFIG_AMOUNT];
	char*		values[CONFIG_AMOUNT];
	char*		defaults[CONFIG_AMOUNT];
}				t_config;

/*
**	This is the global var which holds current state of all the persistent
**	program data (this data is presistent thanks to read/writing an INI file).
*/
t_config		config;

/*
**	If "true", the window mode is fullscreen
*/
#define CONFIG_INDEX_FULLSCREEN	0x00
#define CONFIG_LABEL_FULLSCREEN	"fullscreen"
#define CONFIG_VALUE_FULLSCREEN	"false"
/*
**	If "true", the window is maximized
*/
#define CONFIG_INDEX_MAXIMIZED	0x01
#define CONFIG_LABEL_MAXIMIZED	"window_maximized"
#define CONFIG_VALUE_MAXIMIZED	"false"
/*
**	The current dimensions of the window (irrelevant if fullscreen)
*/
#define CONFIG_INDEX_WINDOW_W	0x02
#define CONFIG_LABEL_WINDOW_W	"window_w"
#define CONFIG_VALUE_WINDOW_W	"640"
#define CONFIG_INDEX_WINDOW_H	0x03
#define CONFIG_LABEL_WINDOW_H	"window_h"
#define CONFIG_VALUE_WINDOW_H	"480"

/*
**	config.c
*/
void	config_make_ini(int fd);
int		config_init();
void	config_save();
void	config_free();
/*
**	config_access.c
*/
char*	config_get(int index);
void	config_set(int index, char* value);

/*
** ************************************************************************** *|
**                           config.ini File Handling                         *|
** ************************************************************************** *|
*/

typedef struct	s_parser
{
	char		*file;
	size_t		index;
	size_t		line;
	char		*name;
	size_t		name_length;
	char		*value;
	size_t		value_length;
}				t_parser;

/*
**	config_ini.c
*/
void	INI_ReadFile(int fd);

#endif
