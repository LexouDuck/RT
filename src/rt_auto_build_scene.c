/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_auto_build_scene.c                              :+:      :+:    :+:   */
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

#include "libft_io.h"
#include "libft_convert.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"
#include "rt_random.h"

static void		write_scene(int fd)
{
	int		i;
	char	*vec;

	write_bgcolor(fd);
	rt_auto_build_cornellbox(fd);
	i = -1;
	while (++i < 7)
	{
		write_enums(fd);
		write_float3(fd, "color:", TYPE_COLOR);
		write_float3(fd, "color2:", TYPE_COLOR);
		ft_write_str(fd, "pos:(");
		vec = ft_f32_to_str(set_alea_nb(TYPE_POS_X) / 1000.0, 5);
		ft_write_str(fd, vec);
		ft_write_str(fd, ", ");
		vec = ft_f32_to_str(set_alea_nb(TYPE_POS_Y) / 1000.0, 5);
		ft_write_str(fd, vec);
		ft_write_str(fd, ", ");
		vec = ft_f32_to_str(set_alea_nb(TYPE_POS_Z) / 1000.0, 5);
		ft_write_str(fd, vec);
		ft_write_str(fd, ")\n");
		ft_write_line(fd, "rot:(0.00000 , 0.00000, 0.00000)");
		write_float3(fd, "scale:", TYPE_FLOAT);
		ft_write_char(fd, '\n');
	}
}

/*
** This function create a file
*/

int				rt_auto_build_scene(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error: Could not write RT file: ", filename, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	ft_srand(g_rt.sdl.current_frame);
	write_scene(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error: Could not close RT file: ", filename, FALSE);
		debug_output_value("close() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	return (filename ? OK : ERROR);
}
