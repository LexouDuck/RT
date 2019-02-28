/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_float3_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft_memory.h"
#include "libft_string.h"
#include "libft_convert.h"
#include "libft_list.h"
#include "rt_cl.h"

cl_float	cl_float3_norm(cl_float3 const *vector)
{
	cl_float	tmp;
	cl_float	sum;

	sum = 0;
	tmp = vector->x;
	tmp *= tmp;
	sum += tmp;
	tmp = vector->y;
	tmp *= tmp;
	sum += tmp;
	tmp = vector->z;
	tmp *= tmp;
	sum += tmp;
	return (sum);
}

void		cl_float3_normalize(cl_float3 *vector)
{
	cl_float		length;

	length = cl_float3_norm(vector);
	if (length > 0)
	{
		length = 1 / sqrt(length);
		vector->x *= length;
		vector->y *= length;
		vector->z *= length;
	}
}

cl_float	cl_float3_dot(cl_float3 *v1, cl_float3 *v2)
{
	cl_float	result;

	result = 0;
	result += (v1->x * v2->x);
	result += (v1->y * v2->y);
	result += (v1->z * v2->z);
	return (result);
}

void		cl_float3_cross(cl_float3 *result, cl_float3 *v1, cl_float3 *v2)
{
	result->x = (v1->y * v2->z) - (v1->z * v2->y);
	result->y = (v1->z * v2->x) - (v1->x * v2->z);
	result->z = (v1->x * v2->y) - (v1->y * v2->x);
}

char		*cl_float3_to_str(cl_float3 *vector, int i)
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
