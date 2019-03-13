/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_auto_build_fix_object.c                         :+:      :+:    :+:   */
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

void			print_static_4(int fd)
{
	ft_write_line(fd, "CUBE");
	ft_write_line(fd, "material:DIFFUSE");
	ft_write_line(fd, "\"Walls Green\"");
	ft_write_line(fd, "color:(0.01000, 1.00000, 0.01000)");
	ft_write_line(fd, "color2:(0.00000, 3.50000, 0.00000)");
	ft_write_line(fd, "pos:(19.70000, 4.45000, 0.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(0.30000, 10.50000, 20.00000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
	ft_write_line(fd, "RECTANGLE");
	ft_write_line(fd, "material:LIGHT");
	ft_write_line(fd, "\"light of the top\"");
	ft_write_line(fd, "color:(1.00000, 1.00000, 1.00000)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(0.00000, 14.90000, 0.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(31.00000, 1.00000, 31.00000)");
	ft_write_line(fd, "bbox_vi:(-0.50000, -0.50000, -0.50000)");
	ft_write_line(fd, "bbox_vf:(0.50000, 0.50000, 0.50000)\n");

}

void			print_static_3(int fd)
{
	ft_write_line(fd, "CUBE");
	ft_write_line(fd, "material:DIFFUSE");
	ft_write_line(fd, "\"walls Blue\"");
	ft_write_line(fd, "color:(0.01000, 0.01000, 1.00000)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(0.00000, 4.45000, -19.50000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(19.00000, 11.0000, 0.50000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
	ft_write_line(fd, "CUBE");
	ft_write_line(fd, "material:DIFFUSE");
	ft_write_line(fd, "\"Walls Red\"");
	ft_write_line(fd, "color:(1.00000, 0.01000, 0.01000)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(-19.70000, 4.50000, 0.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(0.30000, 10.50000, 20.00000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
}

void			print_static_2(int fd)
{
	ft_write_line(fd, "CUBE");
	ft_write_line(fd, "material:DIFFUSE");
	ft_write_line(fd, "\"floor\"");
	ft_write_line(fd, "color:(1.00000, 1.00000, 1.00000)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(0.00000, -7.00000, 0.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(20.00000, 1.00000, 20.00000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
	ft_write_line(fd, "CUBE");
	ft_write_line(fd, "material:DIFFUSE");
	ft_write_line(fd, "\"ceiling\"");
	ft_write_line(fd, "color:(0.26666, 0.26666, 0.26666)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(0.00000, 17.00000, 0.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(20.00000, 2.00000, 20.00000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
}

void			print_static_1(int fd)
{
	ft_write_line(fd, "SPHERE");
	ft_write_line(fd, "material:LIGHT");
	ft_write_line(fd, "color:(1.00000, 1.00000, 1.00000)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(9.00000, 5.00000, 10.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
	ft_write_line(fd, "SPHERE");
	ft_write_line(fd, "material:LIGHT");
	ft_write_line(fd, "color:(1.00000, 1.00000, 1.00000)");
	ft_write_line(fd, "color2:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "pos:(-9.00000, 5.00000, 10.00000)");
	ft_write_line(fd, "rot:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "scale:(0.00000, 0.00000, 0.00000)");
	ft_write_line(fd, "bbox_vi:(-1.00000, -1.00000, -1.00000)");
	ft_write_line(fd, "bbox_vf:(1.00000, 1.00000, 1.00000)\n");
	
}

void			build_fix_object(int fd)
{
	
	print_static_1(fd);
	print_static_2(fd);
	print_static_3(fd);
	print_static_4(fd);
	
}