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
#include <string.h>
#include "libft_memory.h"
#include "libft_io.h"
#include "../rt.h"
#include "debug.h"

static void	config_make_ini(int fd)
{
	int i;

	i = 0;
	while (i < CONFIG_AMOUNT)
	{
		if (rt.config.names[i])
		{
			FT_Write_String(fd, rt.config.names[i]);
			FT_Write_Char(fd, '=');
			if (rt.config.values[i])
				FT_Write_Line(fd, rt.config.values[i]);
			else
				FT_Write_Line(fd, rt.config.defaults[i]);
		}
		++i;
	}
}

static void	config_init_settings(void)
{
	FT_MemoryClear(rt.config.names, CONFIG_AMOUNT * sizeof(char *));
	rt.config.names[CONFIG_INDEX_FULLSCREEN] = CONFIG_LABEL_FULLSCREEN;
	rt.config.names[CONFIG_INDEX_MAXIMIZED] = CONFIG_LABEL_MAXIMIZED;
	rt.config.names[CONFIG_INDEX_WINDOW_W] = CONFIG_LABEL_WINDOW_W;
	rt.config.names[CONFIG_INDEX_WINDOW_H] = CONFIG_LABEL_WINDOW_H;
	FT_MemoryClear(rt.config.values, CONFIG_AMOUNT * sizeof(char *));
	FT_MemoryClear(rt.config.defaults, CONFIG_AMOUNT * sizeof(char *));
	rt.config.defaults[CONFIG_INDEX_FULLSCREEN] = CONFIG_VALUE_FULLSCREEN;
	rt.config.defaults[CONFIG_INDEX_MAXIMIZED] = CONFIG_VALUE_MAXIMIZED;
	rt.config.defaults[CONFIG_INDEX_WINDOW_W] = CONFIG_VALUE_WINDOW_W;
	rt.config.defaults[CONFIG_INDEX_WINDOW_H] = CONFIG_VALUE_WINDOW_H;
}

int			config_init(void)
{
	int	fd;

	config_init_settings();
	if (access(CONFIG_FILE, R_OK) < 0)
	{
	// if file does not exist
		debug_output_value("Using default settings, no ", CONFIG_FILE, FALSE);
		return (OK);
	}
	fd = open(CONFIG_FILE, O_RDONLY, 0644);
	if (fd < 0)
	{
		debug_output_value("Error during config_init() -> "CONFIG_FILE
			" could not be opened for reading: ", strerror(errno), FALSE);
		return (ERROR);
	}
	ini_read_file(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error during config_save() -> "CONFIG_FILE
			" could not be closed correctly: ", strerror(errno), FALSE);
		return (ERROR);
	}
	return (OK);
}

int			config_save(void)
{
	int fd;

	fd = open(CONFIG_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error during config_save() -> "CONFIG_FILE
			" could not be opened for writing: ", strerror(errno), FALSE);
		return (ERROR);
	}
	config_make_ini(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error during config_save() -> "CONFIG_FILE
			" could not be closed correctly: ", strerror(errno), FALSE);
		return (ERROR);
	}
	return (OK);
}

void		config_free(void)
{
	int i;

	i = 0;
	while (i < CONFIG_AMOUNT)
	{
		if (rt.config.values[i])
		{
			free(rt.config.values[i]);
			rt.config.values[i] = NULL;
		}
		++i;
	}
}
