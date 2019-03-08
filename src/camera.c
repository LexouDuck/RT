/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../rt.h"
#include "rt_scene.h"

void		init_camera(t_camera *camera)
{
	camera->mode = CAMERA_MODE_NONE;
	camera->anchor = DEFAULT_CAM_ANCHOR;
	camera->relative_pos = DEFAULT_CAM_POS;
	camera->world_pos = (cl_float3){{
		camera->anchor.x + camera->relative_pos.x,
		camera->anchor.y + camera->relative_pos.y,
		camera->anchor.z + camera->relative_pos.z
	}};
	camera->zoom = 50.0;
	camera->lat = 90;
	camera->lon = 0;
	camera->tilt_angle = DEFAULT_CAM_TILT;
	camera->tilt_vector = (cl_float3){{ 0, 1, 0 }};
	camera->range_min = 0.1;
	camera->range_max = 1000000;
	camera->hrz_fov = DEFAULT_CAM_FOV;
	camera->aperture = DEFAULT_CAM_APERTURE;
	camera->focal_dist = DEFAULT_CAM_FOCALDIST;
	camera->rgb_shade = DEFAULT_CAM_RGB_SHADE;
	camera->rgb_mask = DEFAULT_CAM_RGB_MASK;
	camera_update(camera);
}

void		camera_pan(t_camera *camera, float x, float y)
{
	cl_float3	tmp;
	cl_float3	pan_x;
	cl_float3	pan_y;

	tmp = (cl_float3){{
		-camera->relative_pos.x,
		-camera->relative_pos.y,
		-camera->relative_pos.z
	}};
	cl_float3_cross(&pan_x, &tmp, &camera->tilt_vector);
	cl_float3_cross(&pan_y, &tmp, &pan_x);
	cl_float3_normalize(&pan_x);
	cl_float3_normalize(&pan_y);
	camera->anchor.x -= (x * pan_x.x + y * pan_y.x);
	camera->anchor.y -= (x * pan_x.y + y * pan_y.y);
	camera->anchor.z -= (x * pan_x.z + y * pan_y.z);
}

void		camera_rotate(t_camera *camera, float x, float y)
{
	cl_float	lat;
	cl_float	lon;

	if (x)
	{
		lat = camera->lat + x;
		if (lat < 0.)
			lat += 360.;
		else if (lat >= 360.)
			lat -= 360.;
		camera->lat = lat;
	}
	if (y)
	{
		lon = camera->lon + y;
		if (lon <= -90.)
			lon = -89.9999;
		else if (lon >= 90.)
			lon = 89.9999;
		camera->lon = lon;
	}
}

void		camera_zoom_tilt(t_camera *camera, float x, float y)
{
	cl_float3	tmp;

	if (y)
	{
		tmp = (cl_float3){{
			-camera->relative_pos.x,
			-camera->relative_pos.y,
			-camera->relative_pos.z
		}};
		cl_float3_normalize(&tmp);
		camera->anchor.x += (y * tmp.x);
		camera->anchor.y += (y * tmp.y);
		camera->anchor.z += (y * tmp.z);
	}
	if (x)
	{
		camera->tilt_angle += (x * M_PI / 180);
		if (camera->tilt_angle < 0)
			camera->tilt_angle += 2 * M_PI;
		else if (camera->tilt_angle >= 2 * M_PI)
			camera->tilt_angle -= 2 * M_PI;
		camera->tilt_vector.x = sinf(camera->tilt_angle);
		camera->tilt_vector.y = cosf(camera->tilt_angle);
		camera->tilt_vector.z = sinf(camera->tilt_angle);
	}
}

void		camera_update(t_camera *camera)
{
	cl_float	lat;
	cl_float	lon;
	cl_float	cos;
	cl_float	sin;

	lat = camera->lat * M_PI / 180;
	lon = camera->lon * M_PI / 180;
	cos = cosf(lat);
	sin = sinf(lat);
	camera->relative_pos.x = cos;
	camera->relative_pos.z = sin;
	cos = cosf(lon);
	sin = sinf(lon);
	camera->relative_pos.x = camera->zoom * cos * camera->relative_pos.x;
	camera->relative_pos.y = camera->zoom * sin;
	camera->relative_pos.z = camera->zoom * cos * camera->relative_pos.z;
	camera->world_pos = (cl_float3){{
		camera->anchor.x + camera->relative_pos.x,
		camera->anchor.y + camera->relative_pos.y,
		camera->anchor.z + camera->relative_pos.z
	}};
}
