/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 12:58:58 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "libft_io.h"

#include "debug.h"

int		debug_init(void)
{
	int fd;

	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_write_str(STDERR, "Error in debug_init() -> "DEBUG_FILE
			" could not be opened for writing: ");
		ft_write_line(STDERR, strerror(errno));
		return (ERROR);
	}
	if (close(fd) < 0)
	{
		ft_write_str(STDERR, "Error in debug_init() -> "DEBUG_FILE
			" could not be closed properly: ");
		ft_write_line(STDERR, strerror(errno));
		return (ERROR);
	}
	return (OK);
}

void	debug_output(char const *str)
{
	int fd;

	ft_write_str(STDERR, str);
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_write_str(STDERR, "Error in debug_output() -> "DEBUG_FILE
			" could not be opened for writing: ");
		ft_write_line(STDERR, strerror(errno));
		return ;
	}
	ft_write_str(fd, str);
	if (close(fd) < 0)
	{
		ft_write_str(STDERR, "Error in debug_output() -> "DEBUG_FILE
			" could not be closed properly: ");
		ft_write_line(STDERR, strerror(errno));
		return ;
	}
}

void	debug_output_value(char const *str, char *value, t_bool free_value)
{
	int fd;

	ft_write_str(STDERR, str);
	ft_write_line(STDERR, value);
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_write_str(STDERR, "Error in debug_output_value() -> "DEBUG_FILE
			" could not be opened for writing: ");
		ft_write_line(STDERR, strerror(errno));
		return ;
	}
	ft_write_str(fd, str);
	ft_write_line(fd, value);
	if (free_value)
		free(value);
	if (close(fd) < 0)
	{
		ft_write_str(STDERR, "Error in debug_output_value() -> "DEBUG_FILE
			" could not be closed properly: ");
		ft_write_line(STDERR, strerror(errno));
		return ;
	}
}

void	debug_output_error(char const *str, t_bool sdl_error)
{
	int fd;

	ft_write_line(STDERR, str);
	if (sdl_error)
		ft_write_line(STDERR, SDL_GetError());
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_write_str(STDERR, "Error in debug_output_error() -> "DEBUG_FILE
			" could not be opened for writing: ");
		ft_write_line(STDERR, strerror(errno));
		return ;
	}
	ft_write_line(fd, str);
	if (sdl_error)
		ft_write_line(fd, SDL_GetError());
	if (close(fd) < 0)
	{
		ft_write_str(STDERR, "Error in debug_output_error() -> "DEBUG_FILE
			" could not be closed properly: ");
		ft_write_line(STDERR, strerror(errno));
		return ;
	}
}

int		debug_perror(char const *str)
{
	int fd;

	ft_write_line(STDERR, str);
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_write_str(STDERR, "Error in debug_perror() -> "DEBUG_FILE
			" could not be opened for writing: ");
		ft_write_line(STDERR, strerror(errno));
		return (ERROR);
	}
	ft_write_line(fd, str);
	if (close(fd) < 0)
	{
		ft_write_str(STDERR, "Error in debug_perror() -> "DEBUG_FILE
			" could not be closed properly: ");
		ft_write_line(STDERR, strerror(errno));
		return (ERROR);
	}
	return (ERROR);
}
