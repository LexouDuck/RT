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

#ifndef __CONFIG_H
# define __CONFIG_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

# include "libft.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

# define CONFIG_FILE		"config.ini"

# define CONFIG_AMOUNT	4

/*
**	This struct is meant to hold all persistent program data (in strings).
**	There's only one of these: rt.config, it holds current state of all the
**	persistent program data (this is thanks to read/writing an INI file).
*/

typedef	struct	s_config
{
	char const	*names[CONFIG_AMOUNT];
	char		*values[CONFIG_AMOUNT];
	char		*defaults[CONFIG_AMOUNT];
}				t_config;

/*
**	If "true", the window mode is fullscreen
*/

# define CONFIG_INDEX_FULLSCREEN	0x00
# define CONFIG_LABEL_FULLSCREEN	"fullscreen"
# define CONFIG_VALUE_FULLSCREEN	"false"

/*
**	If "true", the window is maximized
*/

# define CONFIG_INDEX_MAXIMIZED	0x01
# define CONFIG_LABEL_MAXIMIZED	"window_maximized"
# define CONFIG_VALUE_MAXIMIZED	"false"

/*
**	The current dimensions of the window (irrelevant if fullscreen)
*/

# define CONFIG_INDEX_WINDOW_W	0x02
# define CONFIG_LABEL_WINDOW_W	"window_w"
# define CONFIG_VALUE_WINDOW_W	"880"
# define CONFIG_INDEX_WINDOW_H	0x03
# define CONFIG_LABEL_WINDOW_H	"window_h"
# define CONFIG_VALUE_WINDOW_H	"480"

/*
**	config.c
*/

int				config_init();
int				config_save();
void			config_free();

/*
**	config_access.c
*/

char			*config_get(int index);
void			config_set(int index, char *value);

/*
** ************************************************************************** *|
**                           config.ini File Handling                         *|
** ************************************************************************** *|
*/

typedef struct	s_iniparser
{
	char		*file;
	size_t		index;
	size_t		line;
	char		*name;
	size_t		name_length;
	char		*value;
	size_t		value_length;
}				t_iniparser;

/*
**	config_ini.c
*/

void			ini_read_file(int fd);

#endif
