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
		if (g_rt.config.names[i])
		{
			ft_write_str(fd, g_rt.config.names[i]);
			ft_write_char(fd, '=');
			if (g_rt.config.values[i])
				ft_write_line(fd, g_rt.config.values[i]);
			else
				ft_write_line(fd, g_rt.config.defaults[i]);
		}
		++i;
	}
}

static void	config_init_settings(void)
{
	ft_memclr(g_rt.config.names, CONFIG_AMOUNT * sizeof(char *));
	g_rt.config.names[CONFIG_INDEX_FULLSCREEN] = CONFIG_LABEL_FULLSCREEN;
	g_rt.config.names[CONFIG_INDEX_MAXIMIZED] = CONFIG_LABEL_MAXIMIZED;
	g_rt.config.names[CONFIG_INDEX_WINDOW_W] = CONFIG_LABEL_WINDOW_W;
	g_rt.config.names[CONFIG_INDEX_WINDOW_H] = CONFIG_LABEL_WINDOW_H;
	ft_memclr(g_rt.config.values, CONFIG_AMOUNT * sizeof(char *));
	ft_memclr(g_rt.config.defaults, CONFIG_AMOUNT * sizeof(char *));
	g_rt.config.defaults[CONFIG_INDEX_FULLSCREEN] = CONFIG_VALUE_FULLSCREEN;
	g_rt.config.defaults[CONFIG_INDEX_MAXIMIZED] = CONFIG_VALUE_MAXIMIZED;
	g_rt.config.defaults[CONFIG_INDEX_WINDOW_W] = CONFIG_VALUE_WINDOW_W;
	g_rt.config.defaults[CONFIG_INDEX_WINDOW_H] = CONFIG_VALUE_WINDOW_H;
}

int			config_init(void)
{
	int	fd;

	config_init_settings();
	if (access(CONFIG_FILE, R_OK) < 0)
	{
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
		if (g_rt.config.values[i])
		{
			free(g_rt.config.values[i]);
			g_rt.config.values[i] = NULL;
		}
		++i;
	}
}
