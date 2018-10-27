/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_camera	*camera_new(void)
{
	t_camera	*result;

	if (!(result = (t_camera *)malloc(sizeof(t_camera))))
		return (NULL);
	result->mode = CAMERA_NONE;
	result->zoom = 50.0;
	result->render = 0b111;
	result->fov = 80;
	vector_set(&result->anchor, 0, 0, 0);
	vector_set(&result->pos, 0, 0, 0);
	result->lat = 90;
	result->lon = 0;
	result->angle = 0;
	vector_set(&result->tilt, 0, 1, 0);
	result->range_min = 0.1;
	result->range_max = 1000000;
	return (result);
}

void		camera_pan(t_camera *camera, float x, float y)
{
	t_vector	x_axis;
	t_vector	y_axis;

	vector_invert(&camera->pos);
	vector_multiply(&x_axis, &camera->pos, &camera->tilt);
	vector_multiply(&y_axis, &camera->pos, &x_axis);
	vector_invert(&camera->pos);
	vector_normalize(&x_axis);
	vector_normalize(&y_axis);
	camera->anchor.x -= (x * x_axis.x + y * y_axis.x);
	camera->anchor.y -= (x * x_axis.y + y * y_axis.y);
	camera->anchor.z -= (x * x_axis.z + y * y_axis.z);
}

void		camera_rotate(t_camera *camera, float x, float y)
{
	float	lat;
	float	lon;

	if (x)
	{
		lat = camera->lat + x;
		if (lat < 0)
			lat += 360;
		else if (lat >= 360)
			lat -= 360;
		camera->lat = lat;
	}
	if (y)
	{
		lon = camera->lon + y;
		if (lon <= -90)
			lon = -89.99999;
		else if (lon >= 90)
			lon = 89.99999;
		camera->lon = lon;
	}
}

void		camera_zoom_tilt(t_camera *camera, float x, float y)
{
	t_vector	vector;

	if (y)
	{
		vector_set(&vector, camera->pos.x, camera->pos.y, camera->pos.z);
		vector_invert(&vector);
		vector_normalize(&vector);
		camera->anchor.x += (y * vector.x);
		camera->anchor.y += (y * vector.y);
		camera->anchor.z += (y * vector.z);
	}
	if (x)
	{
		camera->angle += (x * M_PI / 180);
		if (camera->angle < 0)
			camera->angle += 2 * M_PI;
		else if (camera->angle >= 2 * M_PI)
			camera->angle -= 2 * M_PI;
		camera->tilt.x = sinf(camera->angle);
		camera->tilt.y = cosf(camera->angle);
		camera->tilt.z = sinf(camera->angle);
	}
}

void		camera_update(t_camera *camera)
{
	float	lat;
	float	lon;
	float	cos;
	float	sin;

	lat = camera->lat * M_PI / 180;
	lon = camera->lon * M_PI / 180;
	cos = cosf(lat);
	sin = sinf(lat);
	camera->pos.x = cos;
	camera->pos.z = sin;
	cos = cosf(lon);
	sin = sinf(lon);
	camera->pos.x *= cos;
	camera->pos.y = sin;
	camera->pos.z *= cos;
	vector_scale(&camera->pos, camera->zoom);
}
