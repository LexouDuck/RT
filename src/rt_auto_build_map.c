/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_auto_build_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "libft.h"
#include "libft_io.h"
#include "libft_list.h"
#include "libft_convert.h"
#include "libft_string.h"
#include "libft_memory.h"

#include "../rt.h"
#include "debug.h"
#include "rt_scene.h"
#include "rt_auto_build_map.h"

int				set_alea_nb(t_random_type type)
{
	int result;

	if (type == TYPE_PRIMITIVE)
		result = ((rand() % 5) + 1);
	else if (type == TYPE_MATERIAL)
		result = (rand() % MATERIALS);
	else if (type == TYPE_FLOAT)
		result = (rand() % 20001) - 10000;
	else if (type == TYPE_COLOR)
		result = (rand() % 1000);
	else if (type == TYPE_POS_X)
		result = (rand() % 20001) - 10000;
	else if (type == TYPE_POS_Y)
		result = (rand() % 4001);
	else if (type == TYPE_POS_Z)
		result = (rand() % 2001) - 1000;
	return (result);
}

/*
** This function chose aleatory value to the object's vector
*/

t_float3		set_float3_nb(t_random_type type)
{
	t_float3	nb;

	nb.x = set_alea_nb(type) / 1000.0;
	nb.y = set_alea_nb(type) / 1000.0;
	nb.z = set_alea_nb(type) / 1000.0;
	return (nb);
}



void			write_scene(int fd)
{
	int		i;
	char	*vec;

	i = -1;
	ft_write_str(fd, "BG #");
	ft_write_line(fd, "808080");
	ft_write_char(fd, '\n');
	build_fix_object(fd);
	while (++i < 7)
	{
		write_enums(fd);
		write_float3(fd, "color:", TYPE_COLOR);
		write_float3(fd, "color2:", TYPE_COLOR);
		ft_write_str(fd, "pos:(");
		vec =ft_f32_to_str(set_alea_nb(TYPE_POS_X) / 1000.0, 5);
		ft_write_str(fd, vec);
		ft_write_str(fd, ", ");
		vec =ft_f32_to_str(set_alea_nb(TYPE_POS_Y) / 1000.0, 5);
		ft_write_str(fd, vec);
		ft_write_str(fd, ", ");
		vec =ft_f32_to_str(set_alea_nb(TYPE_POS_Z) / 1000.0, 5);
		ft_write_str(fd, vec);
		ft_write_str(fd, ")\n");
		ft_write_line(fd, "rot:(0.00000 , 0.00000, 0.00000)");
		write_float3(fd, "scale:", TYPE_FLOAT);
		ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
		ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)");
		ft_write_char(fd, '\n');
	}
}

/*
** This function create a file
*/

int				auto_build_map(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error: Could not write RT file: ", filename, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	srand(time(NULL));
	write_scene(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error: Could not close RT file: ", filename, FALSE);
		debug_output_value("close() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	return (filename ? OK : ERROR);
}


int				main(int argc, char **argv)
{
	int i;

	if (argc == 2)
	{
		if (auto_build_map(argv[1]) == ERROR)
			return (ERROR);
	}
	else
	{
		debug_output("Donne un nom de fichier comme parametre\n");
		return (OK);
	}
	return (OK);
}
