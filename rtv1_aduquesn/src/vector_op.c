/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		vector_invert(t_vector *vector)
{
	vector->x = -(vector->x);
	vector->y = -(vector->y);
	vector->z = -(vector->z);
}

void		vector_normalize(t_vector *vector)
{
	float		length;

	length = vector_length(vector);
	if (length > 0)
	{
		length = 1 / sqrt(length);
		vector->x *= length;
		vector->y *= length;
		vector->z *= length;
	}
}

float		vector_scalar(t_vector *v1, t_vector *v2)
{
	float	result;

	result = 0;
	result += (v1->x * v2->x);
	result += (v1->y * v2->y);
	result += (v1->z * v2->z);
	return (result);
}

inline void	vector_multiply(t_vector *result, t_vector *v1, t_vector *v2)
{
	result->x = (v1->y * v2->z) - (v1->z * v2->y);
	result->y = (v1->z * v2->x) - (v1->x * v2->z);
	result->z = (v1->x * v2->y) - (v1->y * v2->x);
}

void		vector_transform(t_vector *vector, t_matrix *matrix)
{
	float		x;
	float		y;
	float		z;
	t_vector	*tmp;

	x = vector->x;
	y = vector->y;
	z = vector->z;
	tmp = &matrix->t;
	if (tmp->x || tmp->y || tmp->z)
		vector_set(vector, tmp->x, tmp->y, tmp->z);
	else
		vector_set(vector, 0, 0, 0);
	tmp = &matrix->u;
	vector->x += (x * tmp->x);
	vector->y += (x * tmp->y);
	vector->z += (x * tmp->z);
	tmp = &matrix->v;
	vector->x += (y * tmp->x);
	vector->y += (y * tmp->y);
	vector->z += (y * tmp->z);
	tmp = &matrix->w;
	vector->x += (z * tmp->x);
	vector->y += (z * tmp->y);
	vector->z += (z * tmp->z);
}
