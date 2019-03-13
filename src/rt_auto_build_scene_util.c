/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_auto_build_scene_util.c                         :+:      :+:    :+:   */
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

/*
** This is the principal corp of the file, this function print all item
*/

void			write_float3(int fd, char *label, t_random_type type)
{
	char			*tmp;
	t_float3		vector;

	ft_write_str(fd, label);
	vector = set_float3_nb(type);
	if ((tmp = t_float3_to_str(&vector, 5)))
	{
		ft_write_str(fd, tmp);
		free(tmp);
	}
	ft_write_char(fd, '\n');
}

/*
** This function select aleatory object's type
*/

void			write_enums(int fd)
{
	char	*primitives;

	primitives = rt_get_str_primitive(
		(t_primitive)set_alea_nb(TYPE_PRIMITIVE));
	ft_write_str(fd, primitives);
	ft_write_char(fd, '\n');
	ft_write_str(fd, "material:");
	ft_write_str(fd, rt_get_str_material(
		(t_material)set_alea_nb(TYPE_MATERIAL)));
	ft_write_char(fd, '\n');
}

char			*t_float3_to_str(t_float3 *vector, int i)
{
	t_tuple	x;
	t_tuple	y;
	t_tuple	z;
	char	*result;

	x.items = ft_f32_to_str(vector->x, i);
	y.items = ft_f32_to_str(vector->y, i);
	z.items = ft_f32_to_str(vector->z, i);
	x.length = ft_strlen(x.items);
	y.length = ft_strlen(y.items);
	z.length = ft_strlen(z.items);
	if (!(result = (char *)malloc(x.length + y.length + z.length + 7)))
		return (NULL);
	i = 0;
	result[i++] = '(';
	if (ft_memcpy(result + i, x.items, x.length) && (i += x.length + 2))
		free(x.items);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, y.items, y.length) && (i += y.length + 2))
		free(y.items);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, z.items, z.length) && (i += z.length + 2))
		free(z.items);
	ft_memcpy(result + i - 2, ")\0", 2);
	return (result);
}