/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_auto_build_map.h	                            :+:      :+:    :+:   */
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

typedef struct	s_float3
{
	t_float		x;
	t_float		y;
	t_float		z;
}				t_float3;

typedef enum	e_random_type
{
	TYPE_FLOAT = 0,
	TYPE_PRIMITIVE,
	TYPE_MATERIAL,
	TYPE_COLOR,
	TYPE_BBOX,
	TYPE_POS_X,
	TYPE_POS_Y,
	TYPE_POS_Z,
}				t_random_type;



void			write_float3(int fd, char *label, t_random_type type);
void			write_enums(int fd);
char			*t_float3_to_str(t_float3 *vector, int i);
int				set_alea_nb(t_random_type type);
t_float3		set_float3_nb(t_random_type type);
void			write_scene(int fd);
int				auto_build_map(char *filename);
void			build_fix_object(int fd);
void			print_static_1(int fd);
void			print_static_2(int fd);
void			print_static_3(int fd);
void			print_static_4(int fd);