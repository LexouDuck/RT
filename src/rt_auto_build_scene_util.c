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

#include "libft_io.h"

#include "../rt.h"
#include "rt_scene.h"
#include "rt_random.h"

int			set_alea_nb(t_random_type type)
{
	int result;

	result = 0;
	if (type == TYPE_PRIMITIVE)
		result = (ft_rand() % 5) + 1;
	else if (type == TYPE_MATERIAL)
		result = (ft_rand() % MATERIALS);
	else if (type == TYPE_FLOAT)
		result = (ft_rand() % 20001) - 10000;
	else if (type == TYPE_COLOR)
		result = (ft_rand() % 1000);
	else if (type == TYPE_POS_X)
		result = (ft_rand() % 20001) - 10000;
	else if (type == TYPE_POS_Y)
		result = (ft_rand() % 4001);
	else if (type == TYPE_POS_Z)
		result = (ft_rand() % 2001) - 1000;
	return (result);
}

/*
** This function chose aleatory value to the object's vector
*/

cl_float3	set_float3_nb(t_random_type type)
{
	cl_float3	nb;

	nb.x = set_alea_nb(type) / 1000.0;
	nb.y = set_alea_nb(type) / 1000.0;
	nb.z = set_alea_nb(type) / 1000.0;
	return (nb);
}

/*
** This is the principal corp of the file, this function print all item
*/

void		write_float3(int fd, char *label, t_random_type type)
{
	char			*tmp;
	cl_float3		vector;

	ft_write_str(fd, label);
	vector = set_float3_nb(type);
	if ((tmp = cl_float3_to_str(&vector, 5)))
	{
		ft_write_str(fd, tmp);
		free(tmp);
	}
	ft_write_char(fd, '\n');
}

/*
** This function select aleatory object's type
*/

void		write_bgcolor(int fd)
{
	ft_write_str(fd, "BG #");
	ft_write_line(fd, "808080");
	ft_write_char(fd, '\n');
}

void		write_enums(int fd)
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
