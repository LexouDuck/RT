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

	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_init() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return (ERROR);
	}
	if (close(fd) < 0)
	{
		FT_Write_String(STDERR, "Error in debug_init() -> "DEBUG_FILE
			" could not be closed properly: ");
		FT_Write_Line(STDERR, strerror(errno));
		return (ERROR);
	}
	return (OK);
}

void	debug_output(char const *str)
{
	int fd;

#ifdef DEBUG
	FT_Write_String(STDERR, str);
#endif
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return ;
	}
	FT_Write_String(fd, str);
	if (close(fd) < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output() -> "DEBUG_FILE
			" could not be closed properly: ");
		FT_Write_Line(STDERR, strerror(errno));
		return ;
	}
}

void	debug_output_value(char const *str, char *value, t_bool free_value)
{
	int fd;

#ifdef DEBUG
	FT_Write_String(STDERR, str);
	FT_Write_Line(STDERR, value);
#endif
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output_value() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return ;
	}
	FT_Write_String(fd, str);
	FT_Write_Line(fd, value);
	if (free_value)
		free(value);
	if (close(fd) < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output_value() -> "DEBUG_FILE
			" could not be closed properly: ");
		FT_Write_Line(STDERR, strerror(errno));
		return ;
	}
}

void	debug_output_error(char const *str, t_bool sdl_error)
{
	int fd;

#ifdef DEBUG
	if (sdl_error)
	{
		FT_Write_String(STDERR, str);
		FT_Write_Line(STDERR, SDL_GetError());
	}
	else
	{
		FT_Write_Line(STDERR, str);
	}
#endif
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output_error() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return ;
	}
	if (sdl_error)
	{
		FT_Write_String(fd, str);
		FT_Write_Line(fd, SDL_GetError());
	}
	else
		FT_Write_Line(fd, str);
	if (close(fd) < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output_error() -> "DEBUG_FILE
			" could not be closed properly: ");
		FT_Write_Line(STDERR, strerror(errno));
		return ;
	}
}

int		debug_perror(char const *str)
{
	int fd;

#ifdef DEBUG
	FT_Write_String(STDERR, str);
	FT_Write_Char(STDERR, '\n');
#endif
	fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_perror() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return (ERROR);
	}
	FT_Write_Line(fd, str);
	if (close(fd) < 0)
	{
		FT_Write_String(STDERR, "Error in debug_perror() -> "DEBUG_FILE
			" could not be closed properly: ");
		FT_Write_Line(STDERR, strerror(errno));
		return (ERROR);
	}
	return (ERROR);
}
