/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_matrix	*matrix_new(t_vector *u, t_vector *v, t_vector *w, t_vector *t)
{
	t_matrix	*result;

	if (!(result = (t_matrix *)malloc(sizeof(t_matrix))))
		return (NULL);
	result->u = (u ? *u : (t_vector){0, 0, 0});
	result->v = (v ? *v : (t_vector){0, 0, 0});
	result->w = (w ? *w : (t_vector){0, 0, 0});
	result->t = (t ? *t : (t_vector){0, 0, 0});
	return (result);
}

inline void	matrix_set(t_matrix *result, t_vector *u, t_vector *v, t_vector *w)
{
	result->u = *u;
	result->v = *v;
	result->w = *w;
	result->t = (t_vector){0, 0, 0};
}

inline void	matrix_transpose(t_matrix *matrix)
{
	float tmp;

	tmp = matrix->u.y;
	matrix->u.y = matrix->v.x;
	matrix->v.x = tmp;
	tmp = matrix->v.z;
	matrix->v.z = matrix->w.y;
	matrix->w.y = tmp;
	tmp = matrix->u.z;
	matrix->u.z = matrix->w.x;
	matrix->w.x = tmp;
}

void		matrix_inverse(t_matrix *matrix)
{
	t_vector	u;
	t_vector	v;
	t_vector	w;
	double		determinant;

	vector_set(&u, matrix->u.x, matrix->u.y, matrix->u.z);
	vector_set(&v, matrix->v.x, matrix->v.y, matrix->v.z);
	vector_set(&w, matrix->w.x, matrix->w.y, matrix->w.z);
	determinant = u.x * (v.y * w.z - v.z * w.y) -
		u.y * (v.x * w.z - v.z * w.x) +
		u.z * (v.x * w.y - v.y * w.x);
	determinant = 1 / determinant;
	matrix->u.x = (v.y * w.z - w.y * v.z) * determinant;
	matrix->u.y = (w.y * u.z - u.y * w.z) * determinant;
	matrix->u.z = (u.y * v.z - v.y * u.z) * determinant;
	matrix->v.x = (v.z * w.x - w.z * v.x) * determinant;
	matrix->v.y = (w.z * u.x - u.z * w.x) * determinant;
	matrix->v.z = (u.z * v.x - v.z * u.x) * determinant;
	matrix->w.x = (v.x * w.y - w.x * v.y) * determinant;
	matrix->w.y = (w.x * u.y - u.x * w.y) * determinant;
	matrix->w.z = (u.x * v.y - v.x * u.y) * determinant;
}

void		matrix_multiply(t_matrix *m1, t_matrix *m2)
{
	t_vector	*vector;

	vector = &m1->u;
	vector_set(&m1->u,
		vector->x * m2->u.x + vector->y * m2->v.x + vector->z * m2->w.x,
		vector->x * m2->u.y + vector->y * m2->v.y + vector->z * m2->w.y,
		vector->x * m2->u.z + vector->y * m2->v.z + vector->z * m2->w.z);
	vector = &m1->v;
	vector_set(&m1->v,
		vector->x * m2->u.x + vector->y * m2->v.x + vector->z * m2->w.x,
		vector->x * m2->u.y + vector->y * m2->v.y + vector->z * m2->w.y,
		vector->x * m2->u.z + vector->y * m2->v.z + vector->z * m2->w.z);
	vector = &m1->w;
	vector_set(&m1->w,
		vector->x * m2->u.x + vector->y * m2->v.x + vector->z * m2->w.x,
		vector->x * m2->u.y + vector->y * m2->v.y + vector->z * m2->w.y,
		vector->x * m2->u.z + vector->y * m2->v.z + vector->z * m2->w.z);
}
