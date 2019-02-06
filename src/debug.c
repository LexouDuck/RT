/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
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

#include "libft_io.h"

#include "debug.h"

int		debug_init()
{
	if (access(DEBUG_FILE, W_OK) != -1)
	{	// if file exists
		if (remove(DEBUG_FILE))
		{
			debug_output_value("Could not clear "DEBUG_FILE": ", strerror(errno), FALSE);
			return (ERROR);
		}
	}
	return (OK);
}

void	debug_output(char const* str)
{
#ifdef DEBUG
	FT_Write_String(STDERR, str);
#endif
	int fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return;
	}
	FT_Write_String(fd, str);
	if (close(fd) < 0)
		FT_Write_Line(STDERR, strerror(errno));
}

void	debug_output_value(char const* str, char* value, t_bool free_value)
{
#ifdef DEBUG
	FT_Write_String(STDERR, str);
	FT_Write_Line(STDERR, value);
#endif
	int fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output_value() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return;
	}
	FT_Write_String(fd, str);
	FT_Write_Line(fd, value);
	if (free_value)
		free(value);
	if (close(fd) < 0)
		FT_Write_Line(STDERR, strerror(errno));
}

void	debug_output_error(char const* str, t_bool sdl_error)
{
#ifdef DEBUG
	if (sdl_error)
	{
		FT_Write_String(STDERR, str);
		FT_Write_Line(STDERR, SDL_GetError());
	}
	else FT_Write_Line(STDERR, str);
#endif
	int fd = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd < 0)
	{
		FT_Write_String(STDERR, "Error in debug_output_error() -> "DEBUG_FILE
			" could not be opened for writing: ");
		FT_Write_Line(STDERR, strerror(errno));
		return;
	}
	if (sdl_error)
	{
		FT_Write_String(fd, str);
		FT_Write_Line(fd, SDL_GetError());
	}
	else FT_Write_Line(fd, str);
	if (close(fd) < 0)
		FT_Write_Line(STDERR, strerror(errno));
}
