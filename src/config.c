/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "libft_memory.h"
#include "libft_io.h"

#include "../rt.h"
#include "config.h"
#include "debug.h"

void	config_make_ini(int fd)
{
	int i;

	i = 0;
	while (i < CONFIG_AMOUNT)
	{
		if (config.names[i])
		{
			FT_Write_String(fd, config.names[i]);
			FT_Write_Char(fd, '=');
			if (config.values[i])
				FT_Write_Line(fd, config.values[i]);
			else
				FT_Write_Line(fd, config.defaults[i]);
		}
		++i;
	}
}

static void	config_init_settings()
{
	FT_MemoryClear(config.names, CONFIG_AMOUNT * sizeof(char *));
	config.names[CONFIG_INDEX_FULLSCREEN]	= CONFIG_LABEL_FULLSCREEN;
	config.names[CONFIG_INDEX_MAXIMIZED]	= CONFIG_LABEL_MAXIMIZED;
	config.names[CONFIG_INDEX_WINDOW_W]		= CONFIG_LABEL_WINDOW_W;
	config.names[CONFIG_INDEX_WINDOW_H]		= CONFIG_LABEL_WINDOW_H;
	FT_MemoryClear(config.values, CONFIG_AMOUNT * sizeof(char *));
	FT_MemoryClear(config.defaults, CONFIG_AMOUNT * sizeof(char *));
	config.defaults[CONFIG_INDEX_FULLSCREEN]	= CONFIG_VALUE_FULLSCREEN;
	config.defaults[CONFIG_INDEX_MAXIMIZED]		= CONFIG_VALUE_MAXIMIZED;
	config.defaults[CONFIG_INDEX_WINDOW_W]		= CONFIG_VALUE_WINDOW_W;
	config.defaults[CONFIG_INDEX_WINDOW_H]		= CONFIG_VALUE_WINDOW_H;
}

int			config_init()
{
	int	fd;

	config_init_settings();
	if (access(CONFIG_FILE, W_OK) < 0)
	{	// if file does not exist
		debug_output_value("Using default settings, no ", CONFIG_FILE, FALSE);
		return (OK);
	}
	fd = open(CONFIG_FILE, O_RDONLY, 0777);
	if (fd < 0)
	{
		debug_output_value("Error during config_init() -> "CONFIG_FILE
			" could not be opened for reading: ", strerror(errno), FALSE);
		return (ERROR);
	}
	INI_ReadFile(fd);
	close(fd);
	return (OK);
}

void	config_save()
{
	int fd;

	fd = open(CONFIG_FILE, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		debug_output_value("Error during config_save() -> "CONFIG_FILE
			" could not be opened for writing: ", strerror(errno), FALSE);
		return;
	}
	config_make_ini(fd);
	close(fd);
}

void	config_free()
{
	int i;

	i = 0;
	while (i < CONFIG_AMOUNT)
	{
		if (config.values[i])
		{
			free(config.values[i]);
			config.values[i] = NULL;
		}
		++i;
	}
}
