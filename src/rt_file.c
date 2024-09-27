/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2019/02/28 15:03:29 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "libft_memory.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"

int		rt_file_open(char *filepath)
{
	t_rtparser	parser;
	char		*error;

	g_rt.filepath = filepath;
	if (rt_open_file(filepath, &parser))
		return (ERROR);
	if (parser.file)
	{
		ft_memclr(g_rt.scene.objects, sizeof(t_object) * OBJECT_MAX_AMOUNT);
		g_rt.scene.object_amount = 0;
		if ((error = rt_read_file(&parser)))
		{
			debug_output_value("Error: while reading rt file -> at line ",
				ft_s32_to_str(parser.line), TRUE);
			debug_output_error(error, FALSE);
			if (ft_strnequ(error, "Could not resolve label", 23))
				free(error);
			return (ERROR);
		}
		debug_output_value("Successfully opened file: ", filepath, FALSE);
		free(parser.file);
	}
	return (OK);
}

int		rt_file_import(char *filepath)
{
	t_rtparser	parser;
	char		*error;

	if (rt_open_file(filepath, &parser))
		return (ERROR);
	if (parser.file)
	{
		if ((error = rt_read_file(&parser)))
		{
			debug_output_value("Error: while reading rt file -> at line ",
				ft_s32_to_str(parser.line), TRUE);
			debug_output_error(error, FALSE);
			return (ERROR);
		}
		debug_output_value("Successfully imported file: ", filepath, FALSE);
		free(parser.file);
	}
	return (OK);
}

int		rt_file_save(char *filepath)
{
	int		fd;

	fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error: Could not write RT file: ", filepath, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	rt_save(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error: Could not close RT file: ", filepath, FALSE);
		debug_output_value("close() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	debug_output_value("Successfully saved file: ", filepath, FALSE);
	return (OK);
}
