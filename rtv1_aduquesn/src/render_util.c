/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		render_debug(void *mlx, void *win, t_camera *camera)
{
	char	*str;
	t_u32	color;

	color = 0xFFFFFF;
	str = vector_tostr(&camera->anchor, 3);
	mlx_string_put(mlx, win, 10, 20, color, "Anchor:");
	mlx_string_put(mlx, win, 60, 20, color, str);
	free(str);
	str = vector_tostr(&camera->pos, 3);
	mlx_string_put(mlx, win, 10, 40, color, "Vector:");
	mlx_string_put(mlx, win, 60, 40, color, str);
	free(str);
	str = ft_ftoa(camera->lat, 8);
	mlx_string_put(mlx, win, 10, 60, color, "Lat:");
	mlx_string_put(mlx, win, 50, 60, color, str);
	free(str);
	str = ft_ftoa(camera->lon, 8);
	mlx_string_put(mlx, win, 10, 80, color, "Lon:");
	mlx_string_put(mlx, win, 50, 80, color, str);
	free(str);
	str = ft_ftoa(camera->zoom, 8);
	mlx_string_put(mlx, win, 10, 99, color, "Zoom:");
	mlx_string_put(mlx, win, 50, 99, color, str);
	free(str);
}

void		rtv1_read_object_getmatrix(t_object *object)
{
	t_vector	*rot;
	float		tmp;

	rot = &object->rotation;
	vector_set(&object->matrix.u, cosf(rot->y) * cosf(rot->z),
		cosf(rot->y) * sinf(rot->z), -sinf(rot->y));
	tmp = sinf(rot->x) * sinf(rot->y);
	vector_set(&object->matrix.v,
		tmp * cosf(rot->z) - cosf(rot->x) * sinf(rot->z),
		tmp * sinf(rot->z) + cosf(rot->x) * cosf(rot->z),
		sinf(rot->x) * cosf(rot->y));
	tmp = cosf(rot->x) * sinf(rot->y);
	vector_set(&object->matrix.w,
		tmp * cosf(rot->z) + sinf(rot->x) * sinf(rot->z),
		tmp * sinf(rot->z) - sinf(rot->x) * cosf(rot->z),
		cosf(rot->x) * cosf(rot->y));
	object->matrix.t = (t_vector){0, 0, 0};
	object->matrix_toworld.u = object->matrix.u;
	object->matrix_toworld.v = object->matrix.v;
	object->matrix_toworld.w = object->matrix.w;
	matrix_inverse(&object->matrix);
	object->matrix_normal.u = object->matrix.u;
	object->matrix_normal.v = object->matrix.v;
	object->matrix_normal.w = object->matrix.w;
	matrix_transpose(&object->matrix_normal);
}

void		get_camera_matrix(t_camera *camera)
{
	t_vector	axis_forward;
	t_vector	axis_right;
	t_vector	axis_up;

	vector_set(&axis_forward, camera->pos.x, camera->pos.y, camera->pos.z);
	vector_normalize(&axis_forward);
	if (axis_forward.x == 0 && axis_forward.z == 0 &&
		(axis_forward.y == 1 || axis_forward.y == -1))
		axis_forward.z = 0.00001;
	vector_multiply(&axis_right, &camera->tilt, &axis_forward);
	vector_normalize(&axis_right);
	vector_multiply(&axis_up, &axis_forward, &axis_right);
	matrix_set(&camera->matrix, &axis_right, &axis_up, &axis_forward);
	vector_set(&camera->matrix.t,
		camera->anchor.x + camera->pos.x,
		camera->anchor.y + camera->pos.y,
		camera->anchor.z + camera->pos.z);
}

void		set_ray_to_object_space(t_ray *ray, t_object *object)
{
	t_vector	scale;

	scale.x = 1 / object->scale.x;
	scale.y = 1 / object->scale.y;
	scale.z = 1 / object->scale.z;
	ray->pos.x -= object->position.x;
	ray->pos.y -= object->position.y;
	ray->pos.z -= object->position.z;
	vector_transform(&ray->pos, &object->matrix);
	ray->pos.x *= scale.x;
	ray->pos.y *= scale.y;
	ray->pos.z *= scale.z;
	vector_transform(&ray->dir, &object->matrix);
	ray->dir.x *= scale.x;
	ray->dir.y *= scale.y;
	ray->dir.z *= scale.z;
}

void		set_hitposnormal_toworld(t_object *object, t_shader *shader)
{
	shader->hit_pos.x += shader->hit_normal.x * LIGHT_BIAS;
	shader->hit_pos.y += shader->hit_normal.y * LIGHT_BIAS;
	shader->hit_pos.z += shader->hit_normal.z * LIGHT_BIAS;
	shader->hit_pos.x *= object->scale.x;
	shader->hit_pos.y *= object->scale.y;
	shader->hit_pos.z *= object->scale.z;
	vector_transform(&shader->hit_pos, &object->matrix_toworld);
	shader->hit_pos.x += object->position.x;
	shader->hit_pos.y += object->position.y;
	shader->hit_pos.z += object->position.z;
	vector_transform(&shader->hit_normal, &object->matrix_normal);
	vector_normalize(&shader->hit_normal);
}
